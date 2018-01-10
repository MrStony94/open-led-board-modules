const gulp = require('gulp');
const copySpecs = require('../config.json').options.copy;
const args = require('../utils/args.js');

gulp.task('copy', () =>
  copySpecs.forEach(copySpec => {
    if (copySpec.app) {
      gulp
        .src(copySpec.src)
        .pipe(gulp.dest(args.appDir() + copySpec.dest))

    } else if (args.export) {
      gulp
        .src(copySpec.src)
        .pipe(gulp.dest(args.destDir() + copySpec.dest))
    }
  })
);