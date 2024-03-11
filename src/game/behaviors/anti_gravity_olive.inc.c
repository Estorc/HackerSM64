// anti_gravity_olive.inc.c

void bhv_init_anti_grav_olive(void) {
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;
}

void bhv_anti_grav_olive_loop(void) {
    o->oCageAnimKey += 0x800;
    if (o->oCageAnimKey > 0x400) o->oFaceAnglePitch = sins(o->oCageAnimKey*5)*1000;
    else o->oFaceAnglePitch = 0;

    if (o->oDistanceToMario < 0x100 && !o->oAction && o->oOpacity >= 255) {
        o->oAction = 1;
        set_mario_animation(gMarioState, MARIO_ANIM_WATER_STAR_DANCE);
        set_mario_action(gMarioState, ACT_ANTI_GRAVITY_OLIVE, 0);
    }

    s16 yaw;
    s16 pitch;
    switch (o->oAction) {
        case 0:
            cur_obj_scale(1.0f+sins(o->oCageAnimKey)*0.02f);
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
            o->oOpacity += 10;
            if (o->oOpacity > 255) o->oOpacity = 255;
            break;

        case 1:
            cur_obj_scale(1.5f+sins(o->oCageAnimKey)*0.08f);
            o->oOpacity = 255;
            o->oCageAnimKey += 0x1400;
            calculate_angles(gLakituState.pos, gLakituState.focus, &pitch, &yaw);
            o->oPosX = gMarioState->pos[0] + sins(-yaw)*100*coss(-pitch);
            o->oPosY = gMarioState->pos[1]+60 + sins(-pitch)*100;
            o->oPosZ = gMarioState->pos[2] - coss(-yaw)*100*coss(-pitch);
            if (gMarioState->action != ACT_ANTI_GRAVITY_OLIVE) o->oAction = 2;
            break;

        case 2:
            o->oOpacity -= 40;
            cur_obj_scale(o->header.gfx.scale[0]*1.08f);
            if (o->oOpacity <= 0) {
                o->oOpacity = 0;
                o->oAction = 0;
            }

    }
}