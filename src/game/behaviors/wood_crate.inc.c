// wood_crate.inc.c

u8 bhv_wood_crate_on_hit(u8 params) {
    switch (params) {
        case 0:
            if (gMarioState->action & ACT_FLAG_DASHING && gMarioState->forwardVel > 20.0f) {
                obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
                create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                return FALSE;
            }
            if (gMarioState->flags & (MARIO_PUNCHING | MARIO_KICKING | MARIO_TRIPPING)) {
                if (gMarioState->action != ACT_MOVE_PUNCHING || gMarioState->forwardVel >= 0.0f) {
                    if (gMarioState->action == ACT_PUNCHING) {
                        gMarioState->action = ACT_MOVE_PUNCHING;
                    }

                    mario_set_forward_vel(gMarioState, -48.0f);
                    play_sound(SOUND_ACTION_HIT_2, gMarioState->marioObj->header.gfx.cameraToObject);
                    gMarioState->particleFlags |= PARTICLE_TRIANGLE;
                } else if (gMarioState->action & ACT_FLAG_AIR) {
                    mario_set_forward_vel(gMarioState, -16.0f);
                    play_sound(SOUND_ACTION_HIT_2, gMarioState->marioObj->header.gfx.cameraToObject);
                    gMarioState->particleFlags |= PARTICLE_TRIANGLE;
                }
                obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
                create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                return FALSE;
            }
            break;
        case 1:
            if ((gMarioState->action == ACT_GROUND_POUND)) {
                obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
                create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                return FALSE;
            }
            break;
        case 2:
            obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
            create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
            if (!(gMarioState->flags & MARIO_TURBODASH)) {
                gMarioState->vel[1] = 0.0f;
                return TRUE;
            }
            break;
    }
    return TRUE;
}

void bhv_init_wood_crate(void) {
    o->OnHitBehavior = bhv_wood_crate_on_hit;
}