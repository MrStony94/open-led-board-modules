const gulp = require('gulp');
const connect = require('gulp-connect');
const watch = require('gulp-watch');
const docSpec = require('../config.json').options.doc;
const serverConfig = require('../config.json').options.server;

gulp.task('live-doc', ['build-doc'], function() {
  connect.server({
    livereload: true,
    root: docSpec.dest,
    port: serverConfig.basePort + 3
  });
  watch(`${docSpec.dest}/**/*`).pipe(connect.reload());

  gulp.watch(`${docSpec.src}/**/*`, ['update-doc']);

});