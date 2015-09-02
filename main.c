/* an event loop using lib SDL
 */

#include <SDL.h>

extern void audio_callback(void *, unsigned char *, int);
extern int  video_render(int);
extern void init();

unsigned width = 640;
unsigned height = 480;
unsigned int pause = 0;
unsigned int frames = 0;
unsigned int start_tick;

int main(int argc, char *argv[]) {
  unsigned int flags = SDL_OPENGL;
  SDL_AudioSpec audio;
  SDL_Event ev;

  if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'f')
    flags |= SDL_FULLSCREEN;

  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);

  audio.freq     = 44100;
  audio.format   = AUDIO_S16SYS;
  audio.channels = 2;
  audio.samples  = 1024;
  audio.callback = audio_callback;
  audio.userdata = NULL;
  SDL_OpenAudio(&audio, NULL);
  SDL_PauseAudio(0);

  SDL_SetVideoMode(width,height,32,flags);
  SDL_ShowCursor(1);

  init();

  start_tick = SDL_GetTicks();

  while(!SDL_PollEvent(&ev) || ev.type != SDL_QUIT) {
    int t = SDL_GetTicks();

    if (pause==0 && video_render(t)==0) {
      SDL_GL_SwapBuffers();
      frames++;
    }
    if (ev.type == SDL_KEYDOWN) {
      if (ev.key.keysym.sym == SDLK_ESCAPE)
        break;
      if (ev.key.keysym.sym == SDLK_SPACE)
        pause = !pause;
    }
    if (ev.type == SDL_QUIT)
      break;
    SDL_Delay(20);
  }

  printf("FPS: %.1f\n",
    frames / ((SDL_GetTicks() - start_tick) / 1000.0));

  SDL_Quit();

  return 0;
}

