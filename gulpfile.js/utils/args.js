const argv = require('yargs').argv;
const outputDirs = require('../config.json').options.outputDirs;

module.exports.export =  !!argv.export;
module.exports.destDir = () => argv.export ? outputDirs.export.root : outputDirs.dev.root;
module.exports.appDir = () => argv.export ? outputDirs.export.root + outputDirs.export.app : outputDirs.dev.root + outputDirs.dev.app;
