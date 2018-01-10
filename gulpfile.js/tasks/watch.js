const gulp = require('gulp');
const runSequence = require('run-sequence');
const watchConfig = require('../config.json').watch;
const args = require('../utils/args.js');

let sequence = watchConfig.prerequisites;
sequence.push([...new Set(watchConfig.watch.reduce((tasks, spec) => {
  tasks = tasks.concat(spec.tasks);
  return tasks;
}, watchConfig.start))]);

gulp.task('watch', () => {
  runSequence.apply(null, sequence);

  watchConfig.watch.forEach(spec => {
    if (spec.app || args.export) {
      gulp.watch(spec.files, spec.tasks)
    }
  })
});
