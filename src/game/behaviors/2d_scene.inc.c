// 2d_scene.inc.c


// Scale = x220
// Param 1 : X * 10
// Param 2 : Y * 1
// Param 3 : Z * 1
// Param 4 : Camera Distance

// Y = Origin,
// Z = Top

void bhv_init_2d_scene(void) {

    o->oMoveAngleYaw-=0x40;
    o->oHomeX = coss(0x100 * o->oMoveAngleYaw);
    o->oHomeY = sins(0x100 * o->oMoveAngleYaw);
    o->oHomeZ = sins(0x100 * -o->oMoveAngleYaw);
    o->oAction = 0;

}

void bhv_2d_scene_loop(void) {

    f32 dx = o->oPosX - gMarioObject->header.gfx.pos[0];
    f32 dy = o->oPosY - gMarioObject->header.gfx.pos[1];
    f32 dz = o->oPosZ - gMarioObject->header.gfx.pos[2];

    if ((abss(dz) < GET_BPARAM2(o->oBehParams)*100) && (abss(dy) < GET_BPARAM3(o->oBehParams)*100) && (abss(dx) < GET_BPARAM1(o->oBehParams)*10)) {
        f32 dist = sqrtf(dx*dx + dz*dz);
        f32 tx = o->oPosX+o->oHomeX*dist*((dz*o->oHomeZ > 0 || dx*o->oHomeX > 0) ? -1 : 1);
        f32 tz = o->oPosZ+o->oHomeZ*dist*((dz*o->oHomeZ > 0 || dx*o->oHomeX > 0) ? -1 : 1);

        if (gCamera->mode != CAMERA_MODE_FIXED) o->oAction = gCamera->mode;
        gLakituState.forcedYaw = 0x100 * o->oMoveAngleYaw;
        gMarioState->movementType = C2D_SCENE_MOVEMENT;

        set_fixed_mode_base_position(
            gMarioState->pos[0]+o->oHomeY*((f32)GET_BPARAM4(o->oBehParams)*-1000.0f)+o->oHomeX*(10.f),
            gMarioState->pos[1]+500.0f,
            gMarioState->pos[2]+o->oHomeY*(10.f)+o->oHomeX*((f32)GET_BPARAM4(o->oBehParams)*-1000.0f)
        );
        //reset_pan_distance(gCamera);
        gMarioState->pos[0] = tx;
        gMarioState->pos[2] = tz;
        set_camera_mode(gCamera, CAMERA_MODE_FIXED, 0);
    } else if (o->oAction) {
        set_camera_mode(gCamera, o->oAction, 0);
        gMarioState->movementType = NORMAL_MOVEMENT;
        o->oAction = 0;

    }
}