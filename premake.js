var fs = require('fs');
var obj_dir = './obj';
var build_dir = './build';

if (!fs.existsSync(obj_dir)) {
  fs.mkdirSync(obj_dir);
  console.log('Created directory: ' + obj_dir);
}

if (!fs.existsSync(build_dir)) {
  fs.mkdirSync(build_dir);
  console.log('Created directory: ', build_dir);
}

console.log('premake: executed successfully!');
