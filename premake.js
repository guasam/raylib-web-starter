const fs = require('fs');
const path = require('path');

let obj_dir = path.resolve(__dirname, 'obj');
let build_dir = path.resolve(__dirname, 'build');
let prepareDeploy = process.argv.includes('prepare-deploy');

//-----------------------------------------
// Create missing directories for make
//-----------------------------------------

if (!fs.existsSync(obj_dir)) {
  fs.mkdirSync(obj_dir);
  console.log('Created directory: ' + obj_dir);
}

if (!fs.existsSync(build_dir)) {
  fs.mkdirSync(build_dir);
  console.log('Created directory: ', build_dir);
}

console.log('premake: executed successfully!');

//-----------------------------------------
// Prepare deployment
//-----------------------------------------
if (prepareDeploy) {
  const glob = require('glob');

  // Find existing html file to rename as 'index.html'
  glob(build_dir + '/**/*.html', {}, (err, files) => {
    if (!Array.isArray(files) || !files.length) return;
    // Check if first index contains index.html
    if (path.basename(files[0]) === 'index.html') {
      // Remove this file index
      files.splice(0, 1);
    }

    // Copy next file index to index.html
    fs.copyFile(files[0], path.join(build_dir, 'index.html'), (err) => {
      if (err) throw err;
      console.info(`(${path.basename(files[0])}) was copied as (index.html)`);
    });
  });
}
