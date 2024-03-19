// pizza_face.inc.c

#include "game/print.h"
void bhv_init_pizza_face(void) {
}

void bhv_pizza_face_loop(void) {
    if (o->oOpacity < 255) {
        o->oOpacity += 2;
        if (o->oOpacity >= 255) o->oOpacity = 255;
    } else {
        o->oPosX += (gMarioState->pos[0] - o->oPosX)/50;
        o->oPosY += (gMarioState->pos[1] - o->oPosY)/50;
        o->oPosZ += (gMarioState->pos[2] - o->oPosZ)/50;
        if (o->oDistanceToMario < 0x200) {
            gMarioState->health = 0x0;
        }
    }
}