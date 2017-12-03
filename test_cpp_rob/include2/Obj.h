#ifndef OBJ_H
#define OBJ_H

#include "defs.h"

class Obj{
    private:
        int x;
        int y;
        int h;
        int w;
        int nb_Frames;
        int deep_Image;
        int type;
        bool solid;
        bool active;
        SDL_Texture ***image;
    public:
        Obj(int x, int y, int h, int w, int nb_Frames, int deep_Image,\
            const char* img, int type, bool solid, bool active);
        ~Obj();
        int Get_x();
        int Get_y();
        int Get_h();
        int Get_w();
        void draw(Game *game);

};

#endif
