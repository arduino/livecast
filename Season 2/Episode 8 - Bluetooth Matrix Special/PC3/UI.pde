public class UI {
  // vars
  int x = 0, y = 0;   // UI coordinates
  int w = 20, h = 20; // size of the pixel matrix in our self-made pixels
  int s = 20, ms = 2; // size of each pixel in dots
  PIXEL_MATRIX mpix;
  PIXEL_MATRIX pix;
  PALETTE palette;
  ColorPicker cp;
  Textarea codeTextarea;
  CheckBox checkboxInvert;
  CheckBox checkboxCompress;
  Button buttonCopyText;
  String code = "";
  int outputMode = 0;   // by default do not invert every other output array (0)
                        // invert output with (1)
                        // use compression (1 on bit 2)

  // constructor
  UI () {
    mpix = new PIXEL_MATRIX(x + 40, y + 10, ms);
    pix = new PIXEL_MATRIX(x + 40, y + 40, s);
    palette = new PALETTE(x + 40, y + 240, s); // XXX: figure out these default configuration
    cp = new ColorPicker( x + 40 + w * s + 10, y + 40, 200, 200, 255 );
    // UI elements related class
    codeTextarea = cp5.addTextarea("txt")
      .setPosition(x+40, y + h*s + 50)
      .setSize(400, 200)
      .setFont(createFont("courier", 12))
      .setLineHeight(14)
      .setColor(color(128))
      .setColorBackground(color(255, 100))
      .setColorForeground(color(255, 100))
      .showScrollbar();

    codeTextarea.setText("// Text automagically generated");

    checkboxInvert = cp5.addCheckBox("checkBox invert")
      .setPosition(x + 40 + w * s + 10, y + 210)
      .setSize(20, 20)
      .setItemsPerRow(1)
      .addItem("inverted-subsequent LED rows", 0)
      ;

    checkboxCompress = cp5.addCheckBox("checkBox compress")
      .setPosition(x + 40 + w * s + 10, y + 240)
      .setSize(20, 20)
      .setItemsPerRow(1)
      .addItem("compress data, 4:2:2 format", 0)
      ;

    buttonCopyText = cp5.addButton("copy text")
      .setValue(0)
      .setPosition(x + 40 + w * s + 10, y + 270)
      .setSize(200, 19)
      ;
  }

  UI (int _x, int _y) {
    x = _x;
    y= _y;
    mpix = new PIXEL_MATRIX(x + 20, y, ms, false);
    pix = new PIXEL_MATRIX(x + 20, y + 50, s, true);
    palette = new PALETTE(x + 20 + w * s + 10, y + 290, s, true);
    cp = new ColorPicker( x + 20 + w * s + 10, y + 50, 320, 200, 255 );
    // UI elements related class
    codeTextarea = cp5.addTextarea("txt")
      .setPosition(x+20, y + h*s + 60)
      .setSize(400, 200)
      .setFont(createFont("courier", 12))
      .setLineHeight(14)
      .setColor(color(128))
      .setColorBackground(color(255, 100))
      .setColorForeground(color(255, 100))
      .showScrollbar();

    codeTextarea.setText("// Text automagically generated");

    checkboxInvert = cp5.addCheckBox("checkBox invert")
      .setPosition(x + 20 + w * s + 10, y + 340)
      .setSize(20, 20)
      .setItemsPerRow(1)
      .setSpacingColumn(30)
      .setSpacingRow(20)
      .addItem("inverted-subsequent LED rows", 0)
      ;

    checkboxCompress = cp5.addCheckBox("checkBox compress")
      .setPosition(x + 20 + w * s + 10, y + 370)
      .setSize(20, 20)
      .setItemsPerRow(1)
      .setSpacingColumn(30)
      .setSpacingRow(20)
      .addItem("compress data, 4:2:2 format", 0)
      ;

    buttonCopyText = cp5.addButton("copy text")
      .setPosition(x + 20 + w * s + 10, y + 400)
      .setSize(200, 19)
      ;
  }

  // methods
  void update() {
    fill(0);
    textSize(50);
    text("PixelCrafter", x + 70, y + 35);
    textSize(20);
    text(ver, x + 350, y + 35);
    mpix.update();
    pix.update();
    palette.update();
    cp.update();

    // refresh the code
    codeTextarea.clear();
    codeTextarea.setText(code);
  }
}
