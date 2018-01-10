# Open LED Board Project

This is the repo for the first Open LED Board development.

## Use
The distribution files for the Open LED Board are available in the `/OpenLEDBoard` folder.

Upload the files to your Arduino and you're all set.

## Participate

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