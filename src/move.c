#include "../include/move.h"

void move(Game *game, int vx, int vy)
{
  int wPerso = game->perso->w;
  int hPerso = game->perso->h;

  for (uint i=0; i<abs(vx); i++)
  {
    if (!collisionMap(game, game->perso->x + abs(vx)/vx, game->perso->y, wPerso, hPerso))
    {
      game->perso->x+=abs(vx)/vx;
    }
    else
    {
      i = abs(vx);
    }
  }
}

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
  w1--, w2--, h1--, h2--;
  return !(x1+w1<x2 || x1>x2+w2 || y1+h1<y2 || y1>y2+h2);
}

bool collisionMap(Game *game, int x1, int y1, int w1, int h1)
{
  for (int x=0; x<game->wmap; x++)
  {
    for (int y=0; y<game->hmap; y++)
    {
      if (game->map[x][y]->solid)
      {
        if (collision(x1, y1, w1, h1, game->map[x][y]->x, game->map[x][y]->y,
                                       game->map[x][y]->w, game->map[x][y]->h))
        {
          printf("bloc %d %d: %d %d\n\n", x, y, game->map[x][y]->x, game->map[x][y]->y);

          return true;
        }
      }
    }
  }
  return false;
}

void gravite(Perso *perso)
{
  if (perso->jump)
  {
    perso->vSpeed += GRAVITE;
    if (perso->y + perso->h + perso->vSpeed >= 544)
    {
      perso->y = 544 - perso->h;
      perso->jump = 0;
      perso->vSpeed = 0;
      perso->hJumpAct = 0;
    }
    else
    {
      perso->y += perso->vSpeed;
    }
  }
}

void jump(Perso *perso)
{
  perso->vSpeed = -perso->vJump;
  perso->jump = true;
  perso->hJumpAct++;
}
