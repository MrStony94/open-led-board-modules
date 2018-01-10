const gulp = require('gulp');
const scss = require('gulp-sass');
const sourcemaps = require('gulp-sourcemaps');
const prefix = require('gulp-autoprefixer');
const scssSpec = require('../config.json').options.scss;
const args = require('../utils/args.js');
const gulpif = require('gulp-if');

gulp.task('scss', function () {
  return gulp.src(scssSpec.entry)
    .pipe(gulpif(!args.export, sourcemaps.init()))
    .pipe(scss({
      "includePaths": [
        "./node_modules"
      ],
      outputStyle: args.export ? 'compressed' : 'expanded',
    }).on('error', scss.logError))
    .pipe(prefix(scssSpec.browsers))
    .pipe(gulpif(!args.export, sourcemaps.write('./')))
    .pipe(gulp.dest(args.appDir() + scssSpec.dest));
});