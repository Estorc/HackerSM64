// john_pillar.inc.c

#include "engine/surface_load.h"
#include "game/sound_init.h"

void destroy_john_pillar(void) {
    o->oAction = 1;
    o->oCageAnimKey = 0;
    gCurrentArea->musicParam2 = 35;
    set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
    spawn_mist_particles_variable(0, 0, 46.0f);
    spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
    create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
    spawn_object(o, MODEL_PIZZA_FACE, bhvPizzaFace);
}

u8 bhv_john_pillar_on_hit(u8 params) {
    if (!o->oAction)
    switch (params) {
        case 0:
            if (gMarioState->action & ACT_FLAG_DASHING && gMarioState->forwardVel > 20.0f) {
                destroy_john_pillar();
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
                destroy_john_pillar();
                return FALSE;
            }
            break;
        case 1:
            if ((gMarioState->action == ACT_GROUND_POUND)) {
                destroy_john_pillar();
                return FALSE;
            }
            break;
        case 2:
            destroy_john_pillar();
            if (!(gMarioState->flags & MARIO_TURBODASH)) {
                gMarioState->vel[1] = 0.0f;
                return TRUE;
            }
            break;
    }
    return TRUE;
}

void bhv_init_john_pillar(void) {
    o->OnHitBehavior = bhv_john_pillar_on_hit;
    o->header.gfx.scale[0] = 0.8f;
    o->header.gfx.scale[1] = 0.8f;
    o->header.gfx.scale[2] = 0.8f;
}

void bhv_john_pillar_loop(void) {
    o->oCageAnimKey += 0x400;
    switch (o->oAction) {
        case 0:
            load_object_collision_model();
            o->header.gfx.scale[1] = 0.8f+sins(o->oCageAnimKey)*0.02f;
            o->header.gfx.scale[0] = 0.8f+coss(o->oCageAnimKey)*0.02f;
            o->header.gfx.scale[2] = 0.8f+coss(o->oCageAnimKey)*0.02f;
            o->oFaceAnglePitch = sins(o->oCageAnimKey)*500;
            break;

        case 1:
            o->oFaceAnglePitch = -o->oCageAnimKey/2;
            o->oPosZ -= 50;
            o->oPosY += sins(o->oCageAnimKey*2+0x2000)*40;
            if (o->oCageAnimKey < 0) obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
    }
}