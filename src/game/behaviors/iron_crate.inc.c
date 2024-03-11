// iron_crate.inc.c

u8 bhv_iron_crate_on_hit(u8 params) {
    switch (params) {
        case 0:
            if (gMarioState->flags & MARIO_TURBODASH) {
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
            if (gMarioState->flags & MARIO_TURBODASH) {
                obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
                create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                set_mario_action(gMarioState, ACT_HYPER_JUMP,0);
                return FALSE;
            }
            break;
    }
    return TRUE;
}

void bhv_init_iron_crate(void) {
    o->OnHitBehavior = bhv_iron_crate_on_hit;
}