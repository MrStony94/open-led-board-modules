/**
 * This class set the data for the preview
 * @author Martin Steinacher
 * @version 0.1
 */

class Preview{
    /*inputText = '';
    colorText = ''
    colorBg = '';
    rainbowBg = ''*/
    constructor(){

    }

    /**
     * this function set values for the preview
     * @param {data} data contains all values of the inputs
     */

    setPreview(data = {}){
        let setColor = false;
        console.log("preview: ", data);
        for (let cat in data){
            for (let param in data[cat]){

                const value = data[cat][param];
                console.log("value:", value)
                if (cat === "text"){
                    if (param === "scrolltext"){
                        document.getElementById('previewText').innerHTML = value;
                    }
                    if (param === "color"){
                        document.getElementById('previewText').style.color = value;
                    }
                }
                if (cat === "bg"){
                    if (param === "mode"){
                        if (value === 1){
                            document.getElementById('previewContainer').style.background ="-webkit-linear-gradient(left, red, orange, yellow, green, blue, indigo, violet)";
                        }else {
                            setColor = true;
                        }
                    }
                    if (param === "color" && setColor === true){
                        document.getElementById('previewContainer').style.background = value;
                    }
                }
            }
        }

    }
}


export default Preview;