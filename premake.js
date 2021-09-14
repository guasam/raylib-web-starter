var fs = require('fs');
var obj_dir = './obj';
var build_dir = './build';
var prepareDeploy = process.argv.includes('prepare-deploy');

if (prepareDeploy) {
  //-----------------------------------------
  // prepare deployment on ghpages
  //-----------------------------------------
  const glob = require('glob');
  const fs = require('fs');
  var path = require('path');

  // Find existing html file to rename as 'index.html'
  glob(__dirname + '/**/*.html', {}, (err, files) => {
    if (files.length) {
      const source = files[0];
      const destination = path.join(path.dirname(source), 'index.html');
      fs.copyFile(source, destination, (err) => {
        if (err) throw err;
        console.log(`(${path.basename(source)}) was copied as (index.html)`);
      });
    }
  });
} else {
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
}