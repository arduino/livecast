public class ColorPicker 
{
  int x, y, w, h;
  public int c;
  PImage cpImage;

  public ColorPicker ( int x, int y, int w, int h, int c )
  {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.c = c;

    cpImage = new PImage( w, h );

    init();
  }

  private void init ()
  {
    // draw color, the w-40 determines how much space is left from the right
    // the greybar is only 30px width, so the rest is left for the generator
    // to fill in
    int cw = w - 40;
    for ( int i=0; i<cw; i++ ) 
    {
      float nColorPercent = i / (float)cw;
      float rad = (-360 * nColorPercent) * (PI / 180);
      int nR = (int)(cos(rad) * 127 + 128) << 16;
      int nG = (int)(cos(rad + 2 * PI / 3) * 127 + 128) << 8;
      int nB = (int)(Math.cos(rad + 4 * PI / 3) * 127 + 128);
      int nColor = nR | nG | nB;

      setGradient( i, 0, 1, h/2, 0xFFFFFF, nColor );
      setGradient( i, (h/2), 1, h/2, nColor, 0x000000 );
    }

    // draw black/white.
    drawRect( cw, 0, 30, h/2, 0xFFFFFF );
    drawRect( cw, h/2, 30, h/2, 0 );

    // draw grey scale.
    for ( int j=0; j<h; j++ )
    {
      int g = 255 - (int)(j/(float)(h-1) * 255 );
      drawRect( w-30, j, 30, 1, color( g, g, g ) );
    }
  }

  // DC: for some reason red(), green() and blue() were throwing
  // an exception here, so I made my own versions of those functions
  private float iRed(color c) {
    return c >> 16 & 0xFF;
  }

  private float iGreen(color c) {
    return c >> 8 & 0xFF;
  }

  private float iBlue(color c) {
    return c & 0xFF;
  }

  private void setGradient(int x, int y, float w, float h, int c1, int c2 )
  {

    float deltaR = iRed(c2) - iRed(c1);
    float deltaG = iGreen(c2) - iGreen(c1);
    float deltaB = iBlue(c2) - iBlue(c1);

    for (int j = y; j<(y+h); j++)
    {
      int c = color( iRed(c1)+(j-y)*(deltaR/h), iGreen(c1)+(j-y)*(deltaG/h), iBlue(c1)+(j-y)*(deltaB/h) );
      cpImage.set( x, j, c );
    }
  }

  private void drawRect( int rx, int ry, int rw, int rh, int rc )
  {
    for (int i=rx; i<rx+rw; i++) 
    {
      for (int j=ry; j<ry+rh; j++) 
      {
        cpImage.set( i, j, rc );
      }
    }
  }

  // changed name from the original, which was render, for consistency with
  // the rest of the example
  public void update ()
  {
    image( cpImage, x, y );
    if ( mousePressed &&
      mouseX >= x && 
      mouseX < x + w &&
      mouseY >= y &&
      mouseY < y + h )
    {
      c = get( mouseX, mouseY );
    }
    
    // this is the color selection box
    // c should be made public so that other 
    // classes can get the color, I implement a getter
    fill( c );
    rect( x, y+h+10, 20, 20 );
  }

  // the setter
  public void setColor(int _c) {
    c = _c;
  }
  
  // the getter
  public int getColor() {
    return c;
  }
}
