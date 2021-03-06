#ifndef DEF_DEFS
#define DEF_DEFS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_H 640
#define WINDOW_W 1280
#define GRAVITE 2
#define VDOWN 20
#define DEBUG 1
#define SCROLLING_BACKGROUND_X 3
#define SCROLLING_BACKGROUND_Y 2

#define DELAY_SHOOT_DUMMY 10
#define DELAY_SHOOT_PLASMA 10
#define PLASMA_RANGE 60
#define DELAY_HIT_BOKEN 10
#define TIME_HIT_BOKEN DELAY_HIT_BOKEN

#define DEP_DIALOGUE_X 700
#define DEP_DIALOGUE_Y 20

#define BANK_SIZE 500

#include "structs.h"
#include "sin.h"
#include "imagesBank.h"
#include "lvlEditor.h"
#include "dialogues.h"
#include "shoot.h"
#include "move.h"
#include "screen.h"
#include "load.h"
#include "inputs.h"
#include "draw.h"
#include "ia.h"

#endif
