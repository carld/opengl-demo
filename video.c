/*
 * render a frame using opengl functions
 */
#include <math.h>

#include <SDL.h>
#include <SDL_opengl.h>

unsigned char dots[8*8*1024] = { 0 };
unsigned int  dotsw = 1024;
unsigned int  dotsh = 8;

void str_to_pixels(char *str, unsigned char *pixels, unsigned int width, unsigned int height);
void font_to_pixels();

void init() {
  font_to_pixels();
  str_to_pixels(
    " ... EXPERIMENTS IN OPENGL "
    " 1 2 3 4 5 6 7 8 9 0 < = > !    "
    , dots, dotsw, dotsh);

  glDisable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);
#if 1
  glEnable(GL_POINT_SMOOTH);
#endif
  glEnable(GL_LINE_SMOOTH);
#if 1
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
#endif
}

void dots_scroll(unsigned char *dots, unsigned int w, unsigned int h, int dirx) {
  int x,y;
  unsigned char t;
  for(y=0;y<h;y++) {
    if (dirx<0) {
      t = dots[(y*w)+0];
      for(x=0;x<w-1;x++) {
       dots[(y*w)+x] = dots[(y*w)+ x+1];
      }
      dots[(y*w)+w-1] = t;
    }
  }
}
void dot_matrix(int w, int h, int dotsize) {
  int x,y;
  int xspacer = 0, yspacer= 4;
  glPushMatrix();
  glBegin(GL_POINTS);
  for(y=0; y < h; y++) {
    for(x=0; x < w; x++) {
      if ( (dots[(y*dotsw)+x]) != 0x00) {
        glVertex3f(x*(dotsize+xspacer),-y*(dotsize+yspacer),0.0);
      }
    }
  }
  glEnd();
  glPopMatrix();
}

void scroller_render() {
  int i;
  int dotsize = 8;
  int w=256,h=8;
  int n=3;
  glPushMatrix();
  glTranslatef( w/2*dotsize * -1 + w,0,-240);
#if 1
  glRotatef(+15,1,0,0);
  glRotatef(+10,0,1,0);
#endif
  for(i=1; i<n+1; i++)
  {
      glPointSize(16/i);
      glPushMatrix();
      glColor4f(0.5 * i/n, 0.7 * i/n, 1.0 * i/n, 0.2 + i/n) ; /*+(i/n));*/
      dot_matrix(w,h,dotsize);
      glPopMatrix();
  }
  dots_scroll(dots, dotsw, dotsh, -1);
  glPopMatrix();
}

int video_render(int t) {

  static int last_t = 0;

  if (t < last_t + 20)
    return -1;
  last_t = t;

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* 640 / 480 = 1.3 */
#if 1
  glFrustum(-1.3,1.3,-1,1,1,1000);
#else
  glOrtho (0, 640, 480, 0, 0, 1);
#endif

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0,0,-120.0);

  if (0) {
    int x,y,n;
    x = 0;
    glPushMatrix();
    glTranslatef(-120,y-60,0);
    glColor4f(0.5, 0.7, 1.0, 0.2);
    glBegin(GL_POLYGON);
      glVertex3f(-10,-10,0);
      glVertex3f(10,-10,0);
      glVertex3f(10,10,0);
      glVertex3f(-10,10,0);
    glEnd();
    glPopMatrix();
  }

  if (0) {
    /* raster bars */
    int x,y;
    y = 128 * cos( (t / 60) * (180 / 60) * (M_PI / 180.0));
    for (x = -8; x < 8; x++) {
      glColor3f(1.0, 1.0 - abs(x)/8.0, 1.0 - abs(x)/8.0);
      glBegin(GL_LINES);
        glVertex3f(-320,y+x,0);
        glVertex3f(320,y+x,0);
      glEnd();
    }
  }

  if (0) {
    /* sin curve */
    int w = 640, h = 120;
    int x,y;
    glPushMatrix();
    glTranslatef(-w/2, 0, 0);
    glLineWidth(2);
    glColor4f(0.5,0.7,1.0,0.8);

    glRotatef(+15,1,0,0);
    glRotatef(+10,0,1,0);

    glBegin(GL_LINE_STRIP);
    for (x=0; x < 640; x++) {
      y = 120.0 * sin(((180.0 / h) * x + (t % 180)) * (M_PI / 180.0));
      glVertex3f(x,y,0);
    }
    glEnd();
    glPopMatrix();
  }

  if (0) {
    /* circling points */
    int x,y,a=0,r=100,n=8,i;
    glPushMatrix();
    for (a=0+(t/20%10); a < 360+(t/20%10); a+=10) {
      x = r*2 * cos((a) * (M_PI / 180.0));
      y = r * sin((a) * (M_PI / 180.0));

      for(i=1; i<n+1; i++)
      {
          glPointSize(128/i);
          glBegin(GL_POINTS);
            glColor4f(0.5 * i/n, 0.7 * i/n, 1.0 * i/n, 0.2 + i/n) ; /*+(i/n));*/
            glVertex3f(x,y,0);
          glEnd();
      }
    }
    glPopMatrix();
  }

  if (1) {
    scroller_render();
  }

  return 0;
}

