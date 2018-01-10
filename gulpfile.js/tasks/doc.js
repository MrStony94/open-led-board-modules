const gulp = require('gulp');
const connect = require('gulp-connect');
const docSpec = require('../config.json').options.doc;
const serverConfig = require('../config.json').options.server;

gulp.task('doc', ['watch-doc'], function() {
  connect.server({
    livereload: false,
    root: docSpec.dest,
    port: serverConfig.basePort + 2
  });
});