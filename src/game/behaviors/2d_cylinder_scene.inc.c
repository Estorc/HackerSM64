// 2d_cylinder_scene.inc.c


// Scale = x220
// Param 1 : Radius
// Param 2 : Height
// Param 3 : Camera Distance
// Param 4 : Switch (0 View from outside / 1 View from inside)

// Y = Top

void bhv_init_2d_cylinder_scene(void) {

    o->oAction = 0;

}

void bhv_2d_cylinder_scene_loop(void) {

    f32 dx = o->oPosX - gMarioObject->header.gfx.pos[0];
    f32 dy = o->oPosY - gMarioObject->header.gfx.pos[1];
    f32 dz = o->oPosZ - gMarioObject->header.gfx.pos[2];

    if ((o->oAction || sqr(dx) + sqr(dz) < sqr(GET_BPARAM1(o->oBehParams)*100)) && (abss(dy) < GET_BPARAM2(o->oBehParams)*100)) {
        f32 dist;
        s16 yaw;
        s16 pitch;
        Vec3f cPos;
        Vec3f origin;
        vec3f_set(origin, o->oPosX,gMarioState->pos[1],o->oPosZ);
        vec3f_get_dist_and_angle(origin, gMarioState->pos, &dist, &pitch, &yaw);

        if (gCamera->mode != CAMERA_MODE_FIXED) o->oAction = gCamera->mode;
        gLakituState.forcedYaw = (GET_BPARAM4(o->oBehParams) ? yaw : yaw + 0x8000);
        gMarioState->movementType = C2D_CYLINDER_SCENE_MOVEMENT;

        Vec3f goalPos;
        vec3f_set_dist_and_angle(origin, goalPos, GET_BPARAM1(o->oBehParams)*100, pitch, yaw + abss(dist - GET_BPARAM1(o->oBehParams)*100));
        approach_vec3f_asymptotic(gMarioState->pos, goalPos, 0.25f, 0.25f, 0.25f);
        vec3f_set_dist_and_angle(origin, cPos, GET_BPARAM1(o->oBehParams)*100 + (f32)GET_BPARAM3(o->oBehParams)*1000.0f * (GET_BPARAM4(o->oBehParams) ? -1 : 1), pitch, yaw);

        set_fixed_mode_base_position(
            cPos[0],
            gMarioState->pos[1]+500.0f,
            cPos[2]
        );
        set_camera_mode(gCamera, CAMERA_MODE_FIXED, 0);
    } else if (o->oAction) {
        set_camera_mode(gCamera, o->oAction, 0);
        gMarioState->movementType = NORMAL_MOVEMENT;
        o->oAction = 0;

    }
}