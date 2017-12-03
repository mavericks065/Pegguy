#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Screen.h"
#include "Obj.h"
#include "Game.h"


const int WINDOW_W = 1280;
const int WINDOW_H = 640;

enum type_t {EMPTY=48/*0*/, GROUND/*1*/, GROUND_2/*2*/, BOX_DESTROYABLE_EMPTY/*3*/, BALL/*4*/,
      BOX/*5*/, DUMMY_LAUNCHER/*6*/, DUMMY/*7*/, TARGET/*8*/, DOOR/*9*/,
      BOX_DESTROYABLE_BALL=65/*A*/, BOX_DESTROYABLE_DUMMY_LAUNCHER/*B*/, NPC1/*C*/,
      SQUARE/*D*/, CIRCLE/*E*/, TRIANGLE/*F*/, SQUARE_BASE/*G*/, CIRCLE_BASE/*H*/,
      TRIANGLE_BASE/*I*/, MOBILE_PLATFORM=75/*K*/, SECRET_GROUND};

#endif
