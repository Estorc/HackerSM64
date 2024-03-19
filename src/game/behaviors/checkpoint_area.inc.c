// checkpoint_area.inc.c
void bhv_checkpoint_area_loop(void) {

    if (sqr(gMarioState->pos[0] - o->oPosX) + sqr(gMarioState->pos[2] - o->oPosZ) < sqr(GET_BPARAM1(o->oBehParams)*100) && gMarioState->pos[1] > o->oPosY) {
        if (!o->oAction && area_get_warp_node(WARP_NODE_WARP_FLOOR)) {
            o->oAction = 1;
            struct Object *oWarp = area_get_warp_node(WARP_NODE_CHECKPOINT)->object;
            oWarp->oPosX = o->oPosX;
            oWarp->oPosY = o->oPosY;
            oWarp->oPosZ = o->oPosZ;
            oWarp->oMoveAngleYaw = o->oMoveAngleYaw;
        }
    } else if (o->oAction) {
        o->oAction = 0;
    }

}