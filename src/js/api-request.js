/**
 *This is a helper class to send the data wit an http api-request to the board
 *
 * @author Martin Steinacher <sa15b014@technikum-wien.at>
 * @version 0.1
 */
class ApiRequest{
    constructor(){
    }

    /**
     * This function calls the function for generating the urls and call afterwards the function to send data
     * @param {string } data
     * contains the data from the inputs
     */
    api(data = {}){
        const baseUrl = "http://192.168.4.1/";
        console.log("data in api-request", data);
        const textUrl = this.makeTextUrl(baseUrl, data["text"]);
        const bgUrl = this.makeBgUrl(baseUrl, data["bg"]);
        this.sendHttpRequest(textUrl);
        this.sendHttpRequest(bgUrl);

    }

    /**
     * sends the data
     * @param {string} url the url which was created from the ip address and the data
     * @returns {boolean}
     */
    sendHttpRequest(url){
        const httpRequest = new XMLHttpRequest();
        if(!httpRequest){
            alert("Failure");
            return false
        }
        /*httpRequest.onreadystatechange = function () {
             if (httpRequest.readyState === XMLHttpRequest.DONE) {
                 if (httpRequest.status === 200) {
                     alert(httpRequest.responseText);
                 } else {
                     alert('There was a problem with the request.');
                 }
             }
         };*/
        httpRequest.open("get", url,true);
        httpRequest.send();
    }

    /**
     * create the url for the text parameters
     * @param {string} baseUrl ip address
     * @param {string} dataText array of data with values from text inputs
     * @returns {string} string
     */
    makeTextUrl(baseUrl,dataText){
        console.log("datatext",dataText);
        let string = baseUrl;
        string += "sc?";
        for (let param in dataText){
            string += param;
            string += "=";
            if(param === "color"){
                string += dataText[param].substr(1);
            }else{
                string += dataText[param];
            }
            if(!(param === "brightness")){
                string += "&";
            }

        }
        console.log(string);
        return string;

    }
    makeBgUrl(baseUrl,dataBg){
        console.log("databg",dataBg);
        let string = baseUrl;
        string += "bg?";
        for (let param in dataBg){
            string += param;
            string += "=";
            if(param === "color"){
                string += dataBg[param].substr(1);
            }else{
                string += dataBg[param];
            }
            if(!(param === "brightness")){
                string += "&";
            }
        }
        console.log(string);
        return string;
    }
}

export default ApiRequest;