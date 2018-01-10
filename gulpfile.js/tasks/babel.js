
/*
Based on https://gist.github.com/danharper/3ca2273125f500429945
 */

const gulp = require('gulp');
const sourcemaps = require('gulp-sourcemaps');
const source = require('vinyl-source-stream');
const buffer = require('vinyl-buffer');
const browserify = require('browserify');
const watchify = require('watchify');
const babel = require('babelify');
const babelSpecs = require('../config.json').options.babel;
const args = require('../utils/args.js');
const gulpif = require('gulp-if');
const gutil = require('gulp-util');

function compile(watch) {
  const presets = ['env'];

  if (args.export) {
    presets.push('minify')
  }

  let bundler = browserify(
    babelSpecs.entry,
    {
      debug: !args.export
    }
  )
    .transform("babelify", {
      // transform that also includes the bootstrap module in node_modules
      global: true, // the global flag transform all files
//      ignore: /\/node_modules\/(?!bootstrap\/)/, // ?! will match if the given suffix is absent
      //
      presets: presets,
    });

  function rebundle() {
    bundler.bundle()
      .on('error', function(err) { console.error('BROWSERIFY ERROR', err); this.emit('end'); })
      .pipe(source(babelSpecs.destFile))
      .pipe(buffer())
      .pipe(gulpif(!args.export, sourcemaps.init({ loadMaps: true })))
      .pipe(gulpif(!args.export, sourcemaps.write('./')))
      .pipe(gulp.dest(args.appDir() + babelSpecs.dest))
      .on('end', function(){ gutil.log('finished bundling ...'); });
  }

  if (watch) {
    bundler = watchify(bundler);
    bundler.on('update', function() {
      console.log('-> bundling ...');
      rebundle();
    });
  }

  rebundle();
}

function watch() {
  return compile(true);
}

gulp.task('buildES6', () => compile());
gulp.task('watchES6', () => watch());

