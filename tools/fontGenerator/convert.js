const Jimp = require("jimp");
const { exec } = require('child_process');

if (process.argv.length < 4) {
	console.error("Too few arguments : node convert.js font_path output_name");
	return -1;
}

Jimp.read(process.argv[2], (err, font) => {
  if (err) throw err;
  for (let j = 1; j < 12; j+=2) {
	for (let i = 0; i < 84; i+=2) {
		for (let k = 0; k < 8; k++) {
			let rCol = font.getPixelColor(i*8+k+8, j);
			let lCol = font.getPixelColor(i*8+k, j);
			font.setPixelColor(lCol, i*8+k+8, j);
			font.setPixelColor(rCol, i*8+k, j);
		}
	}
  }
  font.write("export.i4.png"); // save
});

exec(`"${__dirname}/../n64graphics" -i ${__dirname}/../../textures/fonts/${process.argv[3]}.bin -g export.i4.png -w 672 -h 12 -f ia4`, (err, stdout, stderr) => {
  if (err) {
    console.log(stderr);
  }
  console.log(stdout);
}); 