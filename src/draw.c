#include "../include/draw.h"

void drawGame(Game *game)
{
  clearScreen(game->screen);
  drawMap(game);
  drawHUD(game);

  SDL_RenderPresent(game->screen->pRenderer);
}

//Affichage de ce que l'on voit à l'écran seulement

void drawMap(Game *game){
    int dep_x;  //Nombre de pixel à passer sur la gauche
    int dep_y;  //Nombre de pixel à passer sur le haut

    if (game->perso->x > WINDOW_W/2){
        if (game->perso->x > game->wmap * 32 - WINDOW_W/2){
            dep_x = game->wmap * 32 - WINDOW_W;
        } else {
            dep_x = game->perso->x - WINDOW_W/2;
        }
    } else {
        dep_x = 0;
    }

    if (game->perso->y + game->perso->h > WINDOW_H){
        dep_y = game->perso->y + game->perso->h - WINDOW_H * 0.9;
        //0.9 est un coefficient qu'on peut modifier de 0.1 à 1
        //Plus il est bas, plus on peut voir en dessous du personnage.
    } else {
        dep_y = 0;
    }

    for (int x = 0; x < WINDOW_W/32 + 1; x++){
        if (x + dep_x/32 >= game->wmap || x + dep_x/32 < 0)    break;
        for (int y = 0; y < WINDOW_H/32 + 1; y++){
            if (y + dep_y/32>= game->hmap)    break;
            switch (game->map[x + dep_x/32][y + dep_y/32]->type){
                case GROUND:
                    drawImage(game->map[x + dep_x/32][y + dep_y/32]->image,
                                x*32 - dep_x%32,
                                y*32 - dep_y%32,
                                game->screen->pRenderer
                    );
                  break;
                case GROUND_2:
                    drawImage(game->map[x + dep_x/32][y + dep_y/32]->image,
                                x*32 - dep_x%32,
                                y*32 - dep_y%32,
                                game->screen->pRenderer
                    );
                  break;
                  
            }
        }
    }
    /*
    *   Faudra afficher tous les objets dans cette fonction,
    *   ou alors renvoyer les valeurs de dep_x et dep_y
    *   et n'afficher que si c'est sur l'écran actuel
    */
    int frame_index = 0;
    if (game->perso->vSpeed !=0){
        frame_index = game->perso->nb_frame - 1;
    } else {
        frame_index = abs((game->perso->x/20)%(game->perso->nb_frame-1));
    }
    drawImage(game->perso->image[frame_index],
                game->perso->x - dep_x,
                game->perso->y-dep_y,
                game->screen->pRenderer
    );
    if (game->perso->hand)
    {
      drawImage(game->perso->hand->image,
                  game->perso->x - dep_x,
                  game->perso->y-dep_y,
                  game->screen->pRenderer);
    }

    int nb_obj = game->nbDynObj;
    for (int i = 0; i < nb_obj; i++){
      if (game->mapObj[i]->active){
        drawImage(game->mapObj[i]->image,
                                game->mapObj[i]->x - dep_x,
                                game->mapObj[i]->y - dep_y,
                                game->screen->pRenderer
                    );
        }
    }
    if (DEBUG){
      consol_d(game, dep_x, dep_y);
  }
}

void drawHUD(Game *game)
{
  SDL_Color color_text = {255, 255, 255, 255};

  //affiche le nombre de billes
  char text[3];
  sprintf(text, "%d", game->hud->nbBalls);
  SDL_Surface *text_surface = TTF_RenderText_Solid(game->font, text, color_text);
  if (!text_surface)
  {
      fprintf(stderr, "drawHUD error: Can't create surface\n");
      return;
  }
  SDL_Texture *text_texture = SDL_CreateTextureFromSurface(game->screen->pRenderer, text_surface);
  if (!text_texture)
  {
      fprintf(stderr, "drawHUD error: Can't create texure\n");
      return;
  }
  drawImage(text_texture, game->hud->xBall + 40, game->hud->yBall - 2, game->screen->pRenderer);
  drawImage(game->hud->ball, game->hud->xBall, game->hud->yBall, game->screen->pRenderer);

  drawImage(game->hud->hearts, game->hud->xHearts, game->hud->yHearts, game->screen->pRenderer);

  SDL_FreeSurface(text_surface);
  SDL_DestroyTexture(text_texture);
}

void consol_d(Game *game, int dep_x, int dep_y){
    char debug_text[50];
    int y = 0, x = 250;

    static int count = 0;
    static double save_t = 0;
    double t = SDL_GetTicks() - save_t;
    count ++;
    sprintf(debug_text, "   fps : %lf", count/(t/1000.0));
    if ((int)t%1000 == 0){
        count = 0;
        save_t = SDL_GetTicks();
    }
    print_line(game, x, y+=20, debug_text);

    sprintf(debug_text, "   dep_x : %d", dep_x);
    print_line(game, x, y+=20, debug_text);
    sprintf(debug_text, "   dep_y : %d", dep_y);
    print_line(game, x, y+=20, debug_text);
    sprintf(debug_text, "   x : %d", game->perso->x);
    print_line(game, x, y+=20, debug_text);
    sprintf(debug_text, "   y : %d", game->perso->y);
    print_line(game, x, y+=20, debug_text);
    sprintf(debug_text, "   x_screen : %d", game->perso->x - dep_x);
    print_line(game, x, y+=20, debug_text);
    sprintf(debug_text, "   y_screen : %d", game->perso->y - dep_y);
    print_line(game, x, y+=20, debug_text);

}

void print_line(Game *game, int x, int y, char *debug_text){
    SDL_Color color_text = {255, 255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(game->font, debug_text, color_text);
    if (!text_surface){
        fprintf(stderr, "consol_d error: Can't create surface\n");
        return;
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(game->screen->pRenderer, text_surface);
    if (!text_texture){
        fprintf(stderr, "consol_d error: Can't create texure\n");
        return;
    }
    drawImage(text_texture, x, y, game->screen->pRenderer);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void clearScreen(Screen *screen)
{
  SDL_SetRenderDrawColor(screen->pRenderer, 0, 0, 0, 255);
  SDL_RenderClear(screen->pRenderer);
}

void drawImage(SDL_Texture *texture, int x, int y, SDL_Renderer *pRenderer)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(pRenderer, texture, NULL, &dest);
}
