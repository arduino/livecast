/*
  Class to store the color schema of an image as
  a way to allow compressed arrays
 */
class PALETTE {
  int index = 0; // latest item in the list
  int rows = 2;
  int columns = 16;
  int x = 0, y = 0;
  int s = 25;       // width and height of pixels
  boolean borderOn = false; // turn on or off the border of pixels
  int PALETTE_SIZE = columns*rows;
  
  public PIXEL[] pix = new PIXEL[PALETTE_SIZE];  // array of pixels
  
  // constructor
  PALETTE() {
    initPixelMatrix();
  }
  
  PALETTE (int _x, int _y) {
    x = _x;
    y = _y;
    initPixelMatrix();
  }

  PALETTE (int _x, int _y, int _s) {
    x = _x;
    y = _y;
    s = _s;
    initPixelMatrix();
  }

  PALETTE (int _x, int _y, int _s, boolean _borderOn) {
    x = _x;
    y = _y;
    s = _s;
    borderOn = _borderOn;
    initPixelMatrix();
  }

  // initializer
  // methods
  void initPixelMatrix() {
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++) {
        pix[i*columns+j] = new PIXEL(0, 0, 0, j*s + x, i*s + y, s, borderOn);  // pixels by default are dark grey
        pix[i*columns+j].px = j;
        pix[i*columns+j].py = i;
      }
  }

/*  void initPixelMatrix() {
    for( int i = 0; i < PALETTE_SIZE; i++)
      pix[i] = new PIXEL(0, 0, 0);
  }
*/

  // getters
  color getPaletteItem(int _i) {
    return pix[_i].c;
  }
  
  String getPalette() {
    String pal = "byte palette[] = {\n";
    for (int i = 0; i < PALETTE_SIZE; i++) {
      pal += int(red(pix[i].c)) + ", ";
      pal += int(green(pix[i].c)) + ", ";
      pal += int(blue(pix[i].c));
      if (i < PALETTE_SIZE - 1)
        pal += ", ";
      if ((i+1) % 4 == 0) {
        pal += "\n";
        println(i);
      }
    }
    pal += "};\n";
    return pal;
  }
  
  // renderer
  void update() {
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        pix[i*columns+j].update();
  }

  // is the mouse over?
  public boolean hover() {
    boolean val = false;
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        if (pix[i*columns+j].hover()) val = true;
    return val;
  }

  // return the number of the pixel being on
  public int pixelOn() {
    int val = -1;
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        if (pix[i*columns+j].hover()) val = i*columns+j;
    return val;
  }

  // setters
  void setPaletteItem(color _c) {
    pix[index].c = _c;
  }
  
  void setNewPaletteItem(color _c) {
    pix[index].c = _c;
    index++;
  }
  
  void setPaletteItem(int _i, color _c) {
    pix[_i].c = _c;
  }
  
  // checker
  int indexOfPalette(color _c) {
    int i = -1;
    for (int j = 0; j < PALETTE_SIZE; j++)
      if (pix[j].c == _c)
        i=j;
    return i;
  }
}
