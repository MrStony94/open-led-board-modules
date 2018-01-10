import Collapse from 'bootstrap/js/src/collapse';
import Tab from 'bootstrap/js/src/tab';
import Modal from 'bootstrap/js/src/modal';

/**
 * This is the main class, where all eventlistener are set and distribute all values to the api and preview class.
 * @author Martin Steinacher
 * @version 0.1
 */

import Data from './data';
import Preview from './preview';
import API from './api-request';
import {initAdmin} from "./admin/index";
const url = window.location.href;
if(url.includes("admin")){
    // admin
    initAdmin();
}else {
    const api = new API();
    const pre = new Preview();
    const data = new Data();
    console.log("DATA:", data.getData());
    const colorRadioBtn = document.getElementById('settings__colorRadioBg');
    const submitBtn = document.getElementById('submitBtn');
    const form  = document.getElementById('form');
    const settingsBtn = document.getElementById('settingsBtn');
    const saveBtn = document.getElementById('settings__saveBtn');
    const cancelBtn = document.getElementById('settings__cancelBtn');
    let dataObject = {};
    let mode = 1;
    pre.setPreview(data.getData());
    const inputs = data.getInputs();
    for (let cat in inputs){
        for (let param in inputs[cat]){
            const input = inputs[cat][param];
            if (param === 'mode') {
                input.addEventListener('change', () => {
                    data.setData(cat,param,1)
                });
                colorRadioBtn.addEventListener('change', () => {
                    data.setData(cat,param,0)
                });
            }
            if (param === 'scrolltext'){
                input.addEventListener('input', () => {
                    data.setData(cat,param,input.value)
                    pre.setPreview(data.getData());
                });
            }
        }
    }

    settingsBtn.addEventListener('click', () =>{
        dataObject = data.getData();
        mode = data.getData("bg","mode");
    });
    cancelBtn.addEventListener('click', () => {
        for (let cat in inputs){
            for (let param in inputs[cat]){
                const input = inputs[cat][param];
                if (param !== "scrolltext"){
                    input.value = dataObject[cat][param]
                }
                if (param === "mode"){
                    if (mode === 1){
                        input.checked = true;
                        colorRadioBtn.checked = false;
                    }
                    else {
                        colorRadioBtn.checked = true;
                        input.checked = false;
                    }
                }
            }
        }
    });

    saveBtn.addEventListener('click', () => {
        for (let cat in inputs){
            for (let param in inputs[cat]){
                const input = inputs[cat][param];
                if (param !== "mode" && param !== "scrolltext"){
                    data.setData(cat,param,input.value);
                }
            }
        }
        pre.setPreview(data.getData());
    });

    form.addEventListener('submit', function (event) {
        event.preventDefault();
        api.api(data.getData());
    });


    submitBtn.addEventListener('click', () => {
        api.api(data.getData());
    });
}


