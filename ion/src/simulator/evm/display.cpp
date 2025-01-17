#include "display.h"
#include "framebuffer.h"
#include <assert.h>
#include <ion/display.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#include "sys_llapi.h"

namespace Ion {
namespace Simulator {
namespace Display {

//uint8_t VRAMBUF[256*128];

void point(unsigned int x,unsigned int y, uint8_t c)
{
	/*
  if((x > 256) || (y > 127)){
    return;
  }
  if(VRAMBUF)
  {
	  VRAMBUF[x + y * 256] = c;
  }*/
  //ll_DispHLine(y, x, x, c);

  //ll_DispVLine(x, y, y, c);
}

void init() {
  // gfxSetScreenFormat(GFX_TOP, GSP_BGR8_OES);
  //  gfxSetScreenFormat(GFX_BOTTOM, GSP_BGR8_OES);
  //gfxSetDoubleBuffering(GFX_BOTTOM, false); 

  //VRAMBUF = (uint8_t *)malloc(256*127);
  //printf("Disp Init\n");
  //memset(VRAMBUF, 0 , 256*127);
  //ll_disp_put_area(VRAMBUF, 0, 0, 255, 126);

}

void quit() {

}

static uint8_t lineBuffer[256];
 
void draw() {
 
	uint8_t c;
	for(int j = 0; j < Ion::Display::Height; j++) {
		for(uint32_t i = 0; i < Ion::Display::Width; i++) {
			      c = (
					Framebuffer::address()[i + j * Ion::Display::Width].blue() +
					Framebuffer::address()[i + j * Ion::Display::Width].green() +
					Framebuffer::address()[i + j * Ion::Display::Width].red()
				) / 3;
				if(i < 256)
					lineBuffer[i] = c;
		}
		
		ll_disp_put_area((uint8_t *)lineBuffer, 0, j, 255, j);
	  }

  //printf("Draw,W:%d, H:%d\n", Ion::Display::Width, Ion::Display::Height);
  //320x240
  /*
  uint8_t c;
  for(int i = 0; i < Ion::Display::Width; i++) {
    for(int j = 0; j < Ion::Display::Height; j++) {

      c = (
      Framebuffer::address()[i + j * Ion::Display::Width].blue() +
      Framebuffer::address()[i + j * Ion::Display::Width].green() +
      Framebuffer::address()[i + j * Ion::Display::Width].red()
      ) / 3
      ;
      

      VRAMBUF[i + j * 256] = c;
      
      //point(i/1.4 ,j/1.9 , 255 - c);
      //point(i ,j , 255 - c);

    }
  }
  */
  //ll_disp_put_area((uint8_t *)Framebuffer::address(), 0, 0, 255, 126);

  /*
  pixels = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
  
  
  for(int i = 0; i < Ion::Display::Width; i++) {
    for(int j = 0; j < Ion::Display::Height; j++) {
      u32 pixel = 239*3 - j*3 + i*3*240 + 3*240*40;
      ((u8*)pixels)[pixel + 0] = Framebuffer::address()[i + j * Ion::Display::Width].blue();
      ((u8*)pixels)[pixel + 1] = Framebuffer::address()[i + j * Ion::Display::Width].green();
      ((u8*)pixels)[pixel + 2] = Framebuffer::address()[i + j * Ion::Display::Width].red();
    }
  }
  
  u8* fb = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
  memcpy(fb, keyboard_bgr, keyboard_bgr_len);
  
  gfxFlushBuffers();
  gfxSwapBuffers();
  
  gspWaitForVBlank();*/
  

}

}
}
}
