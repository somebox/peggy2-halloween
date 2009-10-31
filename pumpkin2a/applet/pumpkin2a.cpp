/* This progam displays Halloween images on a Peggy2.

   Copyright (c) 2009 Jeremy Seitz.  All right reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This software is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this software; if not, see http://www.gnu.org/licenses.
*/

#include <Peggy2.h>
#include <Metro.h>

// declare bitmap data
#include "WProgram.h"
void setup();
void show_ghost();
void show_pumpkin();
void advance_frame(int num_frames);
void loop();
uint32_t pumpkin_1[1][25] = {
{0x00000400, 0x00000600, 0x00001C00, 0x00003800, 0x00007C00, 0x0001FF00, 0x0007FFC0, 0x000FFFE0, 0x001CFE70, 0x003E38F8, 0x003E38F8, 0x007FFFFC, 0x007FEFFC, 0x007FC7FC, 0x007FFFFC, 0x007FFFFC, 0x0039FF38, 0x003C4A78, 0x003E00F8, 0x001F33F0, 0x000FFFE0, 0x0003FFC0, 0x0001FE00, 0x00000000, 0x00000000}
};
uint32_t pumpkin_2[1][25] = {
{0x00000400, 0x00000600, 0x00001C00, 0x00003800, 0x00007C00, 0x0001FF00, 0x0007FFC0, 0x000FFFE0, 0x001CFE70, 0x003E38F8, 0x003E38F8, 0x007FFFFC, 0x007FEFFC, 0x007FC7FC, 0x007FFFFC, 0x0079FF3C, 0x00384A38, 0x003C0078, 0x003C00F8, 0x001F01F0, 0x000FB3E0, 0x0003FFC0, 0x0001FE00, 0x00000000, 0x00000000}
};
uint32_t ghost_x[1][25] = {
{0x00000000, 0x00000000, 0x0001FF80, 0x0003FFC0, 0x0007FFE0, 0x000FFFF0, 0x0019F3F8, 0x0010E1F8, 0x001870FC, 0x001C78FC, 0x001C78FC, 0x001870FC, 0x0010E1FC, 0x001FFFFC, 0x001FFFFC, 0x001FFFFC, 0x001FFFFC, 0x001FFFFC, 0x001FFFFC, 0x001F7F7C, 0x001E3E3C, 0x001C1C1C, 0x00000000, 0x00000000, 0x00000000}
};

int frame = 1;
int row;
int scene = 0;

Metro frame_tempo = Metro(100);
Metro scene_tempo = Metro(10000);

// declare frame buffer
Peggy2 peggy;
Peggy2 ghost;
Peggy2 pumpkin1;
Peggy2 pumpkin2;

void setup()  // run once, when the sketch starts
{
  peggy.HardwareInit();
  for (row = 0; row < 25; row++)
  {
    pumpkin1.WriteRow(row, pumpkin_1[0][row]);
    pumpkin2.WriteRow(row, pumpkin_2[0][row]);
    ghost.WriteRow(row, ghost_x[0][row]);    
  }
}

void show_ghost()
{
  frame_tempo.interval(100);  
  ghost.RefreshAll(1);
  advance_frame(50);
  for (row = 0; row < 25; row++)
  {
    uint32_t val;
    if (frame > 25) {
      val = ghost_x[0][row] >> (uint8_t) (50 - frame);
    } else {
      val = ghost_x[0][row] << (uint8_t) (frame);
    }
    ghost.WriteRow(row, val);
  }
}

void show_pumpkin()
{
  frame_tempo.interval(1000);
  if (frame == 1){
    pumpkin1.RefreshAll(1);  // draw frame buffer 1 time
  } else {
    pumpkin2.RefreshAll(1);  // draw frame buffer 1 time
  }  
  advance_frame(2);
}

void advance_frame(int num_frames)
{
  if (frame_tempo.check() == 1){
    frame = (frame + 1) % num_frames;
  }
}

void loop() // run over and over again
{
  if (scene_tempo.check() == 1){
    scene = (scene + 1) % 2;
  }
  if (scene == 1){
    show_ghost();
  } else {
    show_pumpkin();  
  }
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

