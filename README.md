# asciiViewer
Simple ASCII Art Viewer to apply color pallets to ascii art in the terminal. Only for Windows at the moment.

--- How To Use ---
Path to ASCII Art: 
- Specify the path to a file containing your ASCII art, using either the complete path or the path in relation to the location of the application

Path to Pallet:
- Specify the path to your pallet file, using either the complete path or the path in relation to the location of the application

Switching Between Coloration Modes:
- Press numbers 1-5 to switch between the coloration modes.
- Number 6 shows an ANSI color code reference.

- Mode 1 displays the ASCII art unchanged with no coloration.
- Mode 2 supresses all colors except black and unspecified and displays as white.
- Mode 3 supresses all colors except black, white, grey, and unspecified and displays black as dark grey.
- Mode 4 colorizes the image and replaces spaces with '.'.
- Mode 5 colorizes the image, using both colored text and colored background

Quitting the Application:
- Press q to quit the application.

Formatting Color Pallets: 
- Use a new line for every character to be colored.
- The format is <character> <space> <color code>.
- All characters without a color code will be assigned colors automatically. 
