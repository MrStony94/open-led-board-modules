import Preview from './preview.js';
import ApiRequest from './api-request';

/**
 * This class manage all values and inputs
 * @author Martin Steinacher
 * @version 0.1
 */

class Data {
    constructor() {
        this.inputs = this.initInputs();
        this.data = this.fetchAllData();
    }

    /**
     * Get all the input elements and initialize the input/change event handlers
     * @returns {{text: {scrolltext: Element, wait: Element, color: Element, brightness: Element}, bg: {mode: Element, wait: Element, color: Element, brightness: Element}}}
     *          List of elements by parameter and category - { CATEGORY: { PARAMETER: ELEMENT } }
     */
    initInputs() {
        const inputs = {
            text: {
                scrolltext: document.getElementById('textInput'),
                wait: document.getElementById('settings__delayText'),
                color: document.getElementById('settings__colorText'),
                brightness: document.getElementById('settings__brightnessText')
            },
            bg: {
                mode: document.getElementById('settings__rainbowRadioBg'),
                wait: document.getElementById('settings__delayBg'),
                color: document.getElementById('settings__colorBg'),
                brightness: document.getElementById('settings__brightnessBg')
            }
        }

        console.log("INPUT ELEMENTS:", inputs);

        return inputs;
    }

    /**
     * Read the data of all input elements
     * @returns {Object}
     *          List of values by parameter and category - { CATEGORY: { PARAMETER: VALUE } }
     */
    fetchAllData() {
        let data = {};
        for (let cat in this.inputs) {
            data[cat] = {};
            for (let param in this.inputs[cat]) {
                const input = this.inputs[cat][param];
                if (param === 'mode') {
                    data[cat][param] = input.checked ? 1 : 0;
                } else {
                    data[cat][param] = input.value;
                }
            }
        }

        return data;
    }

    /**
     * Get all values, by category or a single value
     * @example
     * getData() // returns the whole list of values by parameter and category
     * getData(CAT) // returns the list of values by parameter for the category CAT
     * getData(CAT, PARAM) // returns the value of the parameter PARAM of the category CAT
     * @param {string} [cat='']
     *        Category to get the values for
     * @param {string} [param='']
     *        Parameter to get the value of
     * @returns {object|string}
     *        See the example for details
     */
    getData(cat = '', param = '') {
        if (!cat) {
            return this.data

        } else if (!param) {
            return this.data[cat];

        } else {
            return this.data[cat][param];
        }

    }

    /**
     *
     * Get all inputs, by category or a single value
     * @example
     * getInputs() // returns the whole list of inputs by parameter and category
     * getInputs(CAT) // returns the list of inputs by parameter for the category CAT
     * getInputs(CAT, PARAM) // returns the inputs of the parameter PARAM of the category CAT
     * @param {string} [cat='']
     *        Category to get the inputs for
     * @param {string} [param='']
     *        Parameter to get the inputs of
     * @returns {object|string}
     *        See the example for details
     */
    getInputs(cat = '', param = ''){
        if (!cat) {
            return this.inputs

        } else if (!param) {
            return this.inputs[cat];

        } else {
            return this.inputs[cat][param];
        }
    }

    /**
     *
     * Set a value for cat and param
     * @param {string} cat
     *        Category to set the value for
     * @param {string} param
     *        Category to set the value
     * @param {string} value
     */
    setData(cat, param, value) {
        this.data[cat][param] = value;
    }
}

export default Data;