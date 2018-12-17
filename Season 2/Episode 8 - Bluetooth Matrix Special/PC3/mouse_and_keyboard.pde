void mousePressed() {
  // if SHIFT is pressed, capture color, 
  // if CONTROL is pressed, fill up with color
  // if no key is pressed, just draw
  if (keyPressed) {
    if (ui.pix.hover()) {
      if (keyCode == CONTROL) {
        //ui.pix.fillColor(ui.pix.pix[ui.pix.pixelOn()].px, ui.pix.pix[ui.pix.pixelOn()].py, ui.cp.getColor(), ui.pix.pix[ui.pix.pixelOn()].c);
        //ui.mpix.fillColor(ui.mpix.pix[ui.pix.pixelOn()].px, ui.mpix.pix[ui.pix.pixelOn()].py, ui.cp.getColor(), ui.mpix.pix[ui.pix.pixelOn()].c);
      }
      if (keyCode == SHIFT)
        ui.cp.setColor(ui.pix.pix[ui.pix.pixelOn()].c);
    }
  } else {
    // check matrix
    if (ui.pix.hover()) {
      updateColorMatrix();
    }

    // check palette
    if (ui.palette.hover()) {
      updateColorPalette();
    }
  }
}

void mouseReleased() {
  // change text
  ui.code = "";

  // if using compressed mode, print the palette first
  if (ui.checkboxCompress.getItem(0).getValue() == 1)
    ui.code = ui.palette.getPalette() + "\n";

  // update palette, just in case
  ui.pix.initPalette(ui.palette);

  // in any case add the actual pixel array
  ui.code += ui.pix.generateCode(ui.outputMode);

  //XXX: ui.pix.sendToArduino(ui.outputMode);
}

void mouseDragged() {
  // check matrix
  if (ui.pix.hover()) {
    updateColorMatrix();
  }

  // check palette
  if (ui.palette.hover()) {
    updateColorPalette();
  }
}

// updateColor is changing the matrixes and updating
// the palette
void updateColorMatrix() {
  // capture the current color
  color cc = ui.cp.getColor();

  // update matrices
  ui.pix.pix[ui.pix.pixelOn()].c = cc;
  ui.mpix.pix[ui.pix.pixelOn()].c = cc;

  // update palette if the color is not in the palette
  if (ui.palette.indexOfPalette(cc) == -1) {
    ui.palette.setNewPaletteItem(cc);
  }
}

void updateColorPalette() {
  // get the color from the palette
  color cc = ui.palette.pix[ui.palette.pixelOn()].c;

  // update active color with the palette selection
  ui.cp.setColor(cc);
}

// capture events from the cp5 elements
// checkboxes act as flags on outputMode
void controlEvent(ControlEvent theEvent) {
  if (theEvent.isFrom(ui.checkboxInvert)) {
    // checkbox uses arrayValue to store the state of 
    // individual checkbox-items. usage:
    println(ui.checkboxInvert.getItem(0).getValue());
    ui.outputMode |= int(ui.checkboxInvert.getItem(0).getValue());
  }
  if (theEvent.isFrom(ui.checkboxCompress)) {
    // checkbox uses arrayValue to store the state of 
    // individual checkbox-items. usage:
    println(ui.checkboxCompress.getItem(0).getValue());
    ui.outputMode |= 2 * int(ui.checkboxCompress.getItem(0).getValue());
  }
  if (theEvent.isFrom(ui.buttonCopyText)) {
    print("copy text to clipboard");
    GClip.copy(ui.codeTextarea.getText());
  }
}

void sendMarker (int val) {
  myPort.write(val);
  println("sent marker: " + val);
}

void getMarker (int val) {
  println("got marker: " + val);
}
