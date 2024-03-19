// kart.inc.c

#include "engine/surface_collision.h"
#include "game/print.h"


s32 perform_kart_step(struct Object *o);
s32 perform_kart_quarter_step(struct Object *o, Vec3f intendedPos);
s32 perform_kart_ground_step();
static s32 perform_kart_ground_quarter_step(struct Object *o, Vec3f nextPos);

static struct ObjectHitbox sKartHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 1000,
    /* height:            */ 113,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

/*void calc_cam_goal_pos(Vec3f cam_goal_pos, u16 increment) {

    cam_goal_pos[0] = o->oPosX-(0x1000 + increment)*sins(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)+(800.0f*(1+sins(o->oCageAnimKey)*0.02f))*sins(o->oFaceAnglePitch)*sins(o->oFaceAngleYaw)-20.0f*sins(o->oFaceAnglePitch)*absf(sins(o->oFaceAngleYaw));
    cam_goal_pos[1] = o->oPosY+(800.0f*(1+sins(o->oCageAnimKey)*0.02f))*coss(o->oFaceAnglePitch);
    cam_goal_pos[2] = o->oPosZ-(0x1000 + increment)*coss(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)+(800.0f*(1+sins(o->oCageAnimKey)*0.02f))*sins(o->oFaceAnglePitch)*coss(o->oFaceAngleYaw)-20.0f*sins(o->oFaceAnglePitch)*absf(sins(o->oFaceAngleYaw));
    
}

void calc_mario_goal_pos() {

    gMarioState->pos[0] = o->oPosX-0*sins(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)+(200.0f*(1+sins(o->oCageAnimKey)*0.02f))*sins(o->oFaceAnglePitch)*sins(o->oFaceAngleYaw)-20.0f*sins(o->oFaceAnglePitch)*absf(sins(o->oFaceAngleYaw));
    gMarioState->pos[1] = o->oPosY+60.0f+(220.0f*(1+sins(o->oCageAnimKey)*0.02f))*coss(o->oFaceAnglePitch);
    gMarioState->pos[2] = o->oPosZ-0*coss(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)+(200.0f*(1+sins(o->oCageAnimKey)*0.02f))*sins(o->oFaceAnglePitch)*coss(o->oFaceAngleYaw)-20.0f*sins(o->oFaceAnglePitch)*absf(sins(o->oFaceAngleYaw));

}*/

void bhv_init_kart(void) {
    o->oGravity = 3.5f;
    o->oFriction = 1.0f;
    o->oBuoyancy = 1.0f;
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;
    o->oAngleVelYaw = o->oFaceAngleYaw;
    cur_obj_scale(0.5f);
    obj_set_hitbox(o, &sKartHitbox);
}

void bhv_kart_loop(void) {

    /*char text[200];
    sprintf(text, "%f", o->oVelY);
    print_text_centered(200,200,text);*/

    o->oCageAnimKey += 0x800;

    if (o->oDistanceToMario < 0x100 && !o->oAction) {
        set_mario_action(gMarioState, ACT_ROCKET, 0);
        o->oAction = 1;
    }
    s32 collisionFlags = perform_kart_ground_step();
    struct GraphNodeTranslationRotation *rotNode = (struct GraphNodeTranslationRotation *) o->header.next->next;
    rotNode->rotation[1] += 800;

    struct Controller *controller;
    Vec3f cGoalPos;
    switch (o->oAction) {
        case 0:
            /*o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;*/
            break;

        case 1:
            controller = gMarioState->controller;
            cur_obj_scale(0.5f+sins(o->oCageAnimKey)*0.02f);
            s32 modulo;

            if (collisionFlags & OBJ_COL_FLAG_GROUNDED) {
                o->oFaceAngleYaw += -controller->stickX*4 * (o->oForwardVel/50.0f);
                if (gMarioState->input & INPUT_A_DOWN) {
                    approach_f32_asymptotic_bool(&o->oForwardVel, 250.0f, 0.05f);
                    modulo = 0x2000;
                }
                else if (gMarioState->input & INPUT_B_DOWN) {
                    approach_f32_asymptotic_bool(&o->oForwardVel, -100.0f, 0.05f);
                    modulo = 0x8000;
                }
                else {
                    approach_f32_asymptotic_bool(&o->oForwardVel, 0.0f, 0.05f);
                    modulo = 0x4000;
                }
            }

            /*if (o->oCageAnimKey % modulo == 0) {
                struct Object *explosion = spawn_object(o, MODEL_EXPLOSION, bhvRocketExplosion);
                explosion->oGraphYOffset += 100.0f;
            }*/

            /*o->oPosX += 125*sins(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)*o->oForwardVel;
            o->oPosY += -125*sins(o->oFaceAnglePitch)*o->oForwardVel;
            o->oPosZ += 125*coss(o->oFaceAngleYaw)*coss(o->oFaceAnglePitch)*o->oForwardVel;*/
            gMarioState->pos[0] = o->oPosX;
            gMarioState->pos[1] = o->oPosY+20;
            gMarioState->pos[2] = o->oPosZ;
        
            gMarioState->faceAngle[1] = o->oFaceAngleYaw;

            o->oMoveAngleYaw = o->oFaceAngleYaw;

            break;
    }
}


s32 perform_kart_step(struct Object *o) {
    Vec3f intendedPos;
    const f32 numSteps = 4.0f;
    s32 i;
    f32 objVelX = o->oForwardVel * sins(o->oMoveAngleYaw)*coss(o->oFaceAnglePitch);
    f32 objVelZ = o->oForwardVel * coss(o->oMoveAngleYaw)*coss(o->oFaceAnglePitch);

    for (i = 0; i < 4; i++) {
        intendedPos[0] = o->oPosX + objVelX / numSteps;
        intendedPos[1] = o->oPosY + o->oVelY / numSteps;
        intendedPos[2] = o->oPosZ + objVelZ / numSteps;

        if (perform_kart_quarter_step(o, intendedPos) != FALSE) {
            return TRUE;
        }
    }

    return FALSE;
}


s32 perform_kart_quarter_step(struct Object *o, Vec3f intendedPos) {

    Vec3f nextPos;
    struct WallCollisionData upperWall, lowerWall;
    struct Surface *ceil, *floor;

    vec3f_copy(nextPos, intendedPos);

    resolve_and_return_wall_collisions(nextPos, 150.0f, 50.0f, &upperWall);
    resolve_and_return_wall_collisions(nextPos, 30.0f, 50.0f, &lowerWall);

    if (upperWall.numWalls || lowerWall.numWalls) return TRUE;

    f32 floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor)+100;
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
        o->oPosY = floorHeight;
        o->oVelY = 0;
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

static s32 perform_kart_ground_quarter_step(struct Object *o, Vec3f nextPos) {
    struct WallCollisionData lowerWall, upperWall;
    struct Surface *ceil, *floor;

    s16 i;
    s16 wallDYaw;
    s32 oldWallDYaw;

    resolve_and_return_wall_collisions(nextPos, 30.0f, 24.0f, &lowerWall);
    resolve_and_return_wall_collisions(nextPos, 60.0f, 50.0f, &upperWall);

    f32 floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor);
    f32 ceilHeight = find_ceil(o->oPosX, o->oPosY, o->oPosZ, &ceil);

    f32 waterLevel = find_water_level(nextPos[0], nextPos[2]);

    if (floor == NULL) {
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
    }

    /*if ((m->action & ACT_FLAG_RIDING_SHELL) && floorHeight < waterLevel) {
        floorHeight = waterLevel;
        floor = &gWaterSurfacePseudoFloor;
        floor->originOffset = -floorHeight;
    }*/

    if (nextPos[1] > floorHeight + 100.0f) {
        if (nextPos[1] + 160.0f >= ceilHeight) {
            return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
        }

        o->oPosX = nextPos[0];
        o->oPosY = nextPos[1];
        o->oPosZ = nextPos[2];

        //set_mario_floor(m, floor, floorHeight);
        return GROUND_STEP_LEFT_GROUND;
    }

    if (floorHeight + 160.0f >= ceilHeight) {
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
    }

    o->oPosX = nextPos[0];
    o->oPosY = floorHeight;
    o->oPosZ = nextPos[2];

    // H64 TODO: Add config opt & check if floor is slippery
    /*if (!SURFACE_IS_UNSAFE(floor->type)) {
        vec3f_copy(m->lastSafePos, m->pos);
    }*/

    //set_mario_floor(m, floor, floorHeight);

    /*if (m->wall != NULL) {
        oldWallDYaw = abs_angle_diff(m->wallYaw, m->faceAngle[1]);
    } else {
        oldWallDYaw = 0x0;
    }
    for (i = 0; i < upperWall.numWalls; i++) {
        wallDYaw = abs_angle_diff(SURFACE_YAW(upperWall.walls[i]), m->faceAngle[1]);
        if (wallDYaw > oldWallDYaw) {
            oldWallDYaw = wallDYaw;
            set_mario_wall(m, upperWall.walls[i]);
        }

        if (wallDYaw >= DEGREES(60) && wallDYaw <= DEGREES(120)) {
            continue;
        }

        return GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS;
    }*/

    return GROUND_STEP_NONE;
}


s32 perform_kart_ground_step() {
    f32 objX = o->oPosX;
    f32 objY = o->oPosY;
    f32 objZ = o->oPosZ;

    f32 floorY;
    f32 waterY = FLOOR_LOWER_LIMIT_MISC;

    f32 lastForwardVel = o->oForwardVel;
    f32 objVelX = o->oForwardVel * sins(o->oMoveAngleYaw);
    f32 objVelZ = o->oForwardVel * coss(o->oMoveAngleYaw);

    s16 collisionFlags = 0;

    // Find any wall collisions, receive the push, and set the flag.
    if (obj_find_wall(objX + objVelX, objY, objZ + objVelZ, objVelX, objVelZ) == 0) {
        o->oForwardVel = 0;
        collisionFlags += OBJ_COL_FLAG_HIT_WALL;
    }

    floorY = find_floor(objX + objVelX, objY, objZ + objVelZ, &sObjFloor)+100;

    o->oFloor       = sObjFloor;
    o->oFloorHeight = floorY;

    if (turn_obj_away_from_steep_floor(sObjFloor, floorY, objVelX, objVelZ) == 1) {
        waterY = find_water_level(objX + objVelX, objZ + objVelZ);
        if (waterY > objY) {
            calc_new_obj_vel_and_pos_y_underwater(sObjFloor, floorY, objVelX, objVelZ, waterY);
            collisionFlags += OBJ_COL_FLAG_UNDERWATER;
        } else {
            calc_new_obj_vel_and_pos_y(sObjFloor, floorY, objVelX, objVelZ);
        }
    } else {
        // Treat any awkward floors similar to a wall.
        o->oForwardVel = 0;
        collisionFlags +=
            ((collisionFlags & OBJ_COL_FLAG_HIT_WALL) ^ OBJ_COL_FLAG_HIT_WALL);
    }

    obj_update_pos_vel_xz();
    if ((s32) o->oPosY == (s32) floorY) {
        collisionFlags += OBJ_COL_FLAG_GROUNDED;
    }

    if ((s32) o->oVelY == 0) {
        collisionFlags += OBJ_COL_FLAG_NO_Y_VEL;
    }

    // Generate a splash if in water.
    obj_splash((s32) waterY, (s32) o->oPosY);
    if (o->oForwardVel != 0) o->oForwardVel = lastForwardVel;
    return collisionFlags;
}



Gfx *kartWheel(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) node;
    struct MarioBodyState *bodyState = &gBodyStates[asGenerated->parameter];
    s32 action = bodyState->action;

    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = gCurGraphNodeObjectNode;
        struct GraphNodeTranslationRotation *rotNode = (struct GraphNodeTranslationRotation *) node->next;
        struct Camera *camera = gCurGraphNodeCamera->config.camera;

        if (asGenerated->parameter > 0) {
            if (asGenerated->parameter <= 2) {
                rotNode->rotation[2] += (-sinf(gMarioState->controller->stickX/32)*10000 * (absf(obj->oForwardVel)/200.0f) - rotNode->rotation[2])/8;
                //rotNode->translation[1] += sins(obj->oCageAnimKey)*200;
            } else {
                rotNode->rotation[1] += 4000 * ((asGenerated->parameter % 2) ? 1 : -1) * (obj->oForwardVel/50.0f);
                rotNode->translation[2] += (-obj->oVelY-rotNode->translation[2])/4;
            }
        } else {
            rotNode->rotation[1] += (10000 * (gMarioState->controller->stickX/32) * (absf(obj->oForwardVel)/200.0f) - rotNode->rotation[1])/8;
        }
    }
    return NULL;
}