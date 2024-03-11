// mario_dash_clone.inc.c


void bhv_mario_dash_clone_loop(void) {

    o->oPosX = gMarioObject->header.gfx.pos[0];
    o->oPosY = gMarioObject->header.gfx.pos[1];
    o->oPosZ = gMarioObject->header.gfx.pos[2];
}