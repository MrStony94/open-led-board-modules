const gulp = require('gulp');
const del = require('del');
const args = require('../utils/args.js');

gulp.task('clean', () => del(args.destDir()));
