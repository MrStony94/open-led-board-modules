
export function initAdmin(){
    const input_modules = document.getElementById("module-input");
    const input_wifipassword = document.getElementById("wifipassword-input");
    const input_wifiname = document.getElementById("wifiname-input");
    const open_wifi_yes = document.getElementById("open-wifi-yes");
    const open_wifi_no = document.getElementById("open-wifi-no");
    const show_srn_yes = document.getElementById("show-srn-yes");
    const show_srn_no = document.getElementById("show-srn-no");
    const send_btn = document.getElementById("send-settings");
    const input_post1 = document.getElementById("post-input1");
    const input_post2 = document.getElementById("post-input2");
    const input_post3 = document.getElementById("post-input3");

    send_btn.addEventListener('click', ()=>{
        const xhr = new XMLHttpRequest();
        let open_wifi = 0;
        let show_srn = 0;
        if (open_wifi_yes.checked){
            open_wifi = 1;
        } else if (open_wifi_no.checked){
            open_wifi = 0;
        }
        if (show_srn_yes.checked){
            show_srn = 1;
        } else if (show_srn_no.checked){
            show_srn = 0;
        }

        if(input_modules.value !== "" && input_wifiname.value !== "" && input_wifipassword.value !== "" && input_post1.value !== "" && input_post2.value !== "" && input_post3.value !== ""){
            let string = "http://192.168.4.1/as?modules=" + input_modules.value + "&wifiname=" + input_wifiname.value + "&wifipassword=" + input_wifipassword.value + "&openwifi=" + open_wifi + "&showsrn=" + show_srn + "&post1=" + input_post1.value +  "&post2=" + input_post2.value + "&post3=" + input_post3.value;

            xhr.open('get',string,true);
            xhr.send();
        }

    });
}
