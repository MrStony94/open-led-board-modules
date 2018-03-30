# Open LED Board Project

This is the repo for the first Open LED Board development.

## Use
The distribution files for the Open LED Board are available in the `/OpenLEDBoard` folder.

Upload the files to your Arduino and you're all set.

## GULP

### Install
Install gulp globally ...
```
$ npm install gulp -g
```
... and install the project setup
```
$ npm install
```

### Project Structure
The **source** files are located in the `/src` folder.

The **app** files for viewing the app from a **local server** are generated in the `/dev` folder (see section 'App' below).

The files to **upload** to the Arduino are generated in the `/OpenLEDBoard` folder  (see section 'Arduino' below). 

The **docs** are generated in the `/docs` folder (see section 'JSDoc' below).

### Generating and Viewing

#### App

For testing an viewing the app locally, the files are compiled not-minified and with source-maps.

##### View the App
To 
- **build** the app, 
- **watch** the source files, and  
- start a **server**, 

run ...
```
$ gulp app
```
Then open **`http://localhost:8000`** in your browser.

(The files will be recompiled on change, but you need to reload the browser manually to see the changes)

##### Watch the App
To 
- **build** the app,
- **watch** the source files,  
- start a **server**, and
- **livereload** the browser on-change of the files,

run ...
```
$ gulp connect
```
Then open **`http://localhost:8001`** in your browser.

##### Build the App
To build the app without starting a watcher and server, run
```
$ gulp build
``` 
(This will also generate the JSDoc documentation)

#### Arduino

The files for uploading to the Arduino are minified and compiled without sourcemaps for performance reasons.

##### Export for Arduino
To export all files, ready for upload to the Arduino, run
```
$ gulp build --export
``` 
(This will also generate the JSDoc documentation)

##### Watch the Arduino Files
To watch all source files and compile them on-change for upload to the Arduino, run
```
$ gulp watch --export
``` 

#### JSDoc

##### View the Docs
To 
- **build** the docs and 
- start a **server**, 

run ...
```
$ gulp doc
```
Then open **`http://localhost:8002`** in your browser.

##### Watch the Docs
To 
- **build** the docs,
- **watch** the js files,  
- start a **server**, and
- **livereload** the browser on-change of the files

run ...
```
$ gulp live-doc
```
Then open **`http://localhost:8003`** in your browser.

##### Build the Docs
To only generate the JSDoc documentation without starting a watcher and server, run
```
$ gulp build-doc
```

## Firmware

### Open

Open OpenLEDBoard.ino from folder /OpenLEDBoard.

### Settings for Upload

Select under tools:

* Board: "NodeMCU 0.9 (ESÜ-12 Module)"
* CPU Frequency: "80 Mhz"
* Flash Size: "4M (3M SPIFFS)"
* Upload Speed: "115200"
* Port: Port of esp8266

Aftwards press upload button

## Upload Data

### Download

[Go to Download Site](https://github.com/esp8266/arduino-esp8266fs-plugin)

### Upload

* Place data the folder, with the name /data, in the /OpenLEDBoard folder.
* Choose Tools/ESP8266 Sketch Data Upload

## Modules

You can find the module design in /module_design. Convert the FCStd file to a .stl file. 
Afterwards you can put the .stl file in slicer of your choice and convert it to a gcode.
This module can be printed on every 3D printer, if it is not to big.  