// planet_gravity.inc.c


// Scale = x220

void bhv_planet_gravity_loop(void) {

    f32 dx = o->oPosX - gMarioObject->header.gfx.pos[0];
    f32 dz = o->oPosZ - gMarioObject->header.gfx.pos[2];
    f32 dist = sqrtf(dx*dx + dz*dz);

    if (dist < GET_BPARAM2(o->oBehParams)*100) {

        

    }
}