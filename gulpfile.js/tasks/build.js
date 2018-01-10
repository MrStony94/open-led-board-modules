const gulp = require('gulp');
const runSequence = require('run-sequence');
const buildConfig = require('../config.json').build;

const sequence = buildConfig.prerequisites;
sequence.push(buildConfig.run);

gulp.task('build', () => {
  return runSequence.apply(null, sequence);
});