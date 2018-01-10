const gulp = require('gulp');
const cache = require('gulp-cache');
const imagemin = require('gulp-imagemin');
const imageSpec = require('../config.json').options.images;
const args = require('../utils/args.js');

gulp.task('images', () =>
  gulp.src(imageSpec.src)
    .pipe(cache(imagemin(imageSpec.quality)))
    .pipe(gulp.dest(args.appDir() + imageSpec.dest))
);

