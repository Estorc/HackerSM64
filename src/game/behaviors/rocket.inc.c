// rocket.inc.c

#include "game/print.h"
#include "engine/surface_collision.h"


s32 perform_rocket_step(struct Object *o);
s32 perform_rocket_quarter_step(struct Object *o, Vec3f intendedPos);

static struct ObjectHitbox sRocketHitbox = {
    /* interactType:      */ INTERACT_GRABBABLE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 65,
    /* height:            */ 113,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void calc_cam_goal_pos(Vec3f cam_goal_pos, u16 increment) {

    cam_goal_pos[0] = o->oPosX-(0x1000 + increment)*sins(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)+(800.0f*(1+sins(o->oCageAnimKey)*0.02f))*sins(o->oFaceAnglePitch)*sins(o->oFaceAngleYaw)-20.0f*sins(o->oFaceAnglePitch)*absf(sins(o->oFaceAngleYaw));
    cam_goal_pos[1] = o->oPosY+(800.0f*(1+sins(o->oCageAnimKey)*0.02f))*coss(o->oFaceAnglePitch);
    cam_goal_pos[2] = o->oPosZ-(0x1000 + increment)*coss(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)+(800.0f*(1+sins(o->oCageAnimKey)*0.02f))*sins(o->oFaceAnglePitch)*coss(o->oFaceAngleYaw)-20.0f*sins(o->oFaceAnglePitch)*absf(sins(o->oFaceAngleYaw));
    
}

void calc_mario_goal_pos() {

    gMarioState->pos[0] = o->oPosX-0*sins(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)+(200.0f*(1+sins(o->oCageAnimKey)*0.02f))*sins(o->oFaceAnglePitch)*sins(o->oFaceAngleYaw)-20.0f*sins(o->oFaceAnglePitch)*absf(sins(o->oFaceAngleYaw));
    gMarioState->pos[1] = o->oPosY+60.0f+(220.0f*(1+sins(o->oCageAnimKey)*0.02f))*coss(o->oFaceAnglePitch);
    gMarioState->pos[2] = o->oPosZ-0*coss(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)+(200.0f*(1+sins(o->oCageAnimKey)*0.02f))*sins(o->oFaceAnglePitch)*coss(o->oFaceAngleYaw)-20.0f*sins(o->oFaceAnglePitch)*absf(sins(o->oFaceAngleYaw));

}

void bhv_init_rocket(void) {
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;
    o->oAngleVelYaw = o->oFaceAngleYaw;
    o->oForwardVel = 125.0f;
    obj_set_hitbox(o, &sRocketHitbox);
}

void bhv_rocket_loop(void) {

    o->oCageAnimKey += 0x800;

    if (o->oDistanceToMario < 0x100 && !o->oAction) {
        set_mario_animation(gMarioState, MARIO_ANIM_DIVE);
        set_mario_action(gMarioState, ACT_ROCKET, 0);
        set_camera_mode(gCamera, CAMERA_MODE_FIXED, 0);
        gMarioState->movementType = ROCKET_MOVEMENT;
        o->oFaceAngleRoll = 0;
        o->oAction = 1;
    }

    struct Controller *controller;
    Vec3f cGoalPos;
    switch (o->oAction) {
        case 0:
            cur_obj_scale(1.0f+sins(o->oCageAnimKey)*0.02f);
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
            if (o->oCageAnimKey > 0x400) o->oFaceAngleRoll = sins(o->oCageAnimKey*5)*1000;
            else o->oFaceAngleRoll = 0;
            break;

        case 1:
            controller = gMarioState->controller;
            o->oFaceAngleYaw += -controller->stickX*4;
            o->oFaceAnglePitch += -controller->stickY*4;
            cur_obj_scale(1.0f+sins(o->oCageAnimKey)*0.02f);
            s32 modulo;

            if (gMarioState->input & INPUT_A_DOWN) {
                approach_f32_asymptotic_bool(&o->oForwardVel, 250.0f, 0.05f);
                modulo = 0x2000;
            }
            else if (gMarioState->input & INPUT_B_DOWN) {
                approach_f32_asymptotic_bool(&o->oForwardVel, 62.5f, 0.05f);
                modulo = 0x8000;
            }
            else {
                approach_f32_asymptotic_bool(&o->oForwardVel, 125.0f, 0.05f);
                modulo = 0x4000;
            }

            if (o->oCageAnimKey % modulo == 0) {
                struct Object *explosion = spawn_object(o, MODEL_EXPLOSION, bhvRocketExplosion);
                explosion->oGraphYOffset += 100.0f;
            }

            /*o->oPosX += 125*sins(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)*o->oForwardVel;
            o->oPosY += -125*sins(o->oFaceAnglePitch)*o->oForwardVel;
            o->oPosZ += 125*coss(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)*o->oForwardVel;*/
            o->oVelY = -sins(o->oFaceAnglePitch)*o->oForwardVel;
            o->oMoveAngleYaw = o->oFaceAngleYaw;
            calc_mario_goal_pos();
            gMarioState->faceAngle[1] = o->oFaceAngleYaw;
            gMarioState->faceAngle[0] = o->oFaceAnglePitch;


            if (o->oPosX < o->oHomeX - 0x6600 - 0x1000) {
                o->oPosX += 23970;
                calc_mario_goal_pos();
                gMarioState->marioObj->header.gfx.pos[0] += 23970;

                uintptr_t *behaviorAddr = segmented_to_virtual(bhvRocketExplosion);
                struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
                struct Object *obj = (struct Object *) listHead->next;

                while (obj != (struct Object *) listHead) {
                    if (obj->behavior == behaviorAddr
                        && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
                        && obj != o
                    ) {
                        obj->oPosX += 23970;
                        obj->header.gfx.pos[0] = obj->oPosX;
                    }

                    obj = (struct Object *) obj->header.next;
                }

                behaviorAddr = segmented_to_virtual(bhvRocketObstacle);
                listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
                obj = (struct Object *) listHead->next;

                while (obj != (struct Object *) listHead) {
                    if (obj->behavior == behaviorAddr
                        && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
                        && obj != o
                    ) {
                        if (obj->oPosX < gCamera->pos[0]) {
                            if (obj->oAction) {
                                struct Object *obstacle = spawn_object(o, MODEL_NONE, bhvRocketObstacle);
                                obstacle->oPosX = obj->oPosX;
                                obstacle->oPosY = obj->oPosY;
                                obstacle->oPosZ = obj->oPosZ;
                                obstacle->oFaceAngleYaw = obj->oFaceAngleYaw;
                                obstacle->oFaceAnglePitch = obj->oFaceAnglePitch;
                                obstacle->oAction = 0;
                                obj->oPosX += 23970;
                                obj->header.gfx.pos[0] = obj->oPosX;
                            }
                        } else {
                            obj_mark_for_deletion(obj);
                        }
                    }

                    obj = (struct Object *) obj->header.next;
                }

                behaviorAddr = segmented_to_virtual(bhvPizzaFace);
                listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
                obj = (struct Object *) listHead->next;

                while (obj != (struct Object *) listHead) {
                    if (obj->behavior == behaviorAddr
                        && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
                        && obj != o
                    ) {
                        obj->oPosX += 23970;
                        obj->header.gfx.pos[0] = obj->oPosX;
                    }

                    obj = (struct Object *) obj->header.next;
                }

                /*calc_cam_goal_pos(cGoalPos, 0);
                set_fixed_mode_base_position(
                    cGoalPos[0],
                    cGoalPos[1],
                    cGoalPos[2]
                );*/

                gPlayerCameraState[0].pos[0] += 23970;
                gCamera->pos[0] += 23970;
                gCamera->focus[0] += 23970;
                gLakituState.goalPos[0] += 23970;
                gLakituState.goalFocus[0] += 23970;
                get_lakitu_old_position()[0] += 23970;
                get_lakitu_old_focus()[0] += 23970;
                gLakituState.pos[0] += 23970;
                gLakituState.focus[0] += 23970;
                gLakituState.curPos[0] += 23970;
                gLakituState.curFocus[0] += 23970;
            }
            calc_cam_goal_pos(cGoalPos, 0);
            set_fixed_mode_base_position(
                    cGoalPos[0],
                    cGoalPos[1],
                    cGoalPos[2]
            );

            if (perform_rocket_step(o)/* || o->oPosY + o->oVelY + 200.0f > find_ceil(o->oPosX, o->oPosY, o->oPosZ, &ceil)*/) {
                spawn_object(o, MODEL_BOWSER_FLAMES, bhvBowserBombExplosion);
                create_sound_spawner(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION);
                set_camera_shake_from_point(SHAKE_POS_LARGE, o->oPosX, o->oPosY, o->oPosZ);
                set_camera_mode(gCamera, -1, 0);
                gMarioState->health = 0x0;
                set_mario_action(gMarioState, ACT_SOFT_BONK, 0);
                o->oAction = 2;
            }

            break;


        case 2:
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
            o->oFaceAngleYaw = o->oAngleVelYaw;
            o->oFaceAnglePitch = 0;
            o->oAction = 0;

    }
}


void bhv_init_rocket_obstacle(void) {

    o->oAction = random_u16()%4+1;
    switch (o->oAction) {

        case 1:
            obj_set_collision_data(o, rocket_obstacle_1_collision);
            cur_obj_set_model(MODEL_ROCKET_OBSTACLE_1);
            o->oAngleVelRoll = random_u16()%0x400;
            o->oAngleVelRoll *= (o->oAngleVelRoll & 1) ? 1 : -1;
            break;

        case 2:
            obj_set_collision_data(o, rocket_obstacle_2_collision); 
            cur_obj_set_model(MODEL_ROCKET_OBSTACLE_2);
            o->oAngleVelRoll = random_u16()%0x150;
            o->oAngleVelRoll *= (o->oAngleVelRoll & 1) ? 1 : -1;
            break;

        case 3:
            obj_set_collision_data(o, rocket_obstacle_3_collision);
            cur_obj_set_model(MODEL_ROCKET_OBSTACLE_3);
            o->oAngleVelRoll = random_u16()%0x400;
            o->oAngleVelRoll *= (o->oAngleVelRoll & 1) ? 1 : -1;
            break;

        case 4:
            obj_set_collision_data(o, rocket_obstacle_4_collision);
            cur_obj_set_model(MODEL_ROCKET_OBSTACLE_4);
            o->oAngleVelRoll = random_u16()%0x400;
            o->oAngleVelRoll *= (o->oAngleVelRoll & 1) ? 1 : -1;
            break;

    }

    o->oCollisionDistance = 5000;

}


void bhv_rocket_obstacle_loop(void) {

    o->oFaceAngleRoll += o->oAngleVelRoll;

}


s32 perform_rocket_step(struct Object *o) {
    Vec3f intendedPos;
    const f32 numSteps = 4.0f;
    s32 i;
    f32 objVelX = o->oForwardVel * sins(o->oMoveAngleYaw)*coss(o->oFaceAnglePitch);
    f32 objVelZ = o->oForwardVel * coss(o->oMoveAngleYaw)*coss(o->oFaceAnglePitch);

    for (i = 0; i < 4; i++) {
        intendedPos[0] = o->oPosX + objVelX / numSteps;
        intendedPos[1] = o->oPosY + o->oVelY / numSteps;
        intendedPos[2] = o->oPosZ + objVelZ / numSteps;

        if (perform_rocket_quarter_step(o, intendedPos) != FALSE) {
            return TRUE;
        }
    }


    return FALSE;
}


s32 perform_rocket_quarter_step(struct Object *o, Vec3f intendedPos) {

    Vec3f nextPos;
    struct WallCollisionData upperWall, lowerWall;
    struct Surface *ceil, *floor;

    vec3f_copy(nextPos, intendedPos);

    resolve_and_return_wall_collisions(nextPos, 150.0f, 50.0f, &upperWall);
    resolve_and_return_wall_collisions(nextPos, 30.0f, 50.0f, &lowerWall);

    if (upperWall.numWalls || lowerWall.numWalls) return TRUE;

    f32 floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor);
    f32 ceilHeight = find_ceil(o->oPosX, o->oPosY, o->oPosZ, &ceil);

    //! The water pseudo floor is not referenced when your intended qstep is
    // out of bounds, so it won't detect you as landing.

    if (floor == NULL) {
        return TRUE;
    }

    //! This check uses f32, but findFloor uses short (overflow jumps)
    if (nextPos[1] <= floorHeight) {
        if (ceilHeight - floorHeight > 160.0f) {
            o->oPosX = nextPos[0];
            o->oPosZ = nextPos[2];
        }
        return TRUE;
    }

    if (nextPos[1] + 160.0f > ceilHeight) {
        if (o->oVelY >= 0.0f) {
            o->oVelY = 0.0f;
        }

        return TRUE;
    }

    o->oPosX = nextPos[0];
    o->oPosY = nextPos[1];
    o->oPosZ = nextPos[2];
    return FALSE;
}