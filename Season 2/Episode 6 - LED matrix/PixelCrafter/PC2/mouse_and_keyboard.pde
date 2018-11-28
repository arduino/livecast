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
    if (ui.pix.hover()) {
      ui.pix.pix[ui.pix.pixelOn()].c = ui.cp.getColor();
      ui.mpix.pix[ui.pix.pixelOn()].c = ui.cp.getColor();
    }
  }
}

void mouseReleased() {
  // change text
  ui.code = ui.pix.generateCode(ui.outputMode);
  //XXX: ui.pix.sendToArduino(ui.outputMode);
}

void mouseDragged() {
  if (ui.pix.hover()) {
    ui.pix.pix[ui.pix.pixelOn()].c = ui.cp.getColor();
    ui.mpix.pix[ui.pix.pixelOn()].c = ui.cp.getColor();
  }
}

// capture events from the cp5 elements
void controlEvent(ControlEvent theEvent) {
  if (theEvent.isFrom(ui.checkbox)) {
    // checkbox uses arrayValue to store the state of 
    // individual checkbox-items. usage:
    println(ui.checkbox.getItem(0).getValue());
    ui.outputMode = int(ui.checkbox.getItem(0).getValue());
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
