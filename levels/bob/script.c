#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/bob/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bob_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _generic_yay0SegmentRomStart, _generic_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group3_yay0SegmentRomStart, _group3_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group1_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group12_geoSegmentRomStart, _group12_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0(0x6, _group12_mio0SegmentRomStart, _group12_mio0SegmentRomEnd), 
	LOAD_MIO0(0x5, _group1_mio0SegmentRomStart, _group1_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	JUMP_LINK(script_func_global_13), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_CHAIN_CHOMP_GATE, bob_geo_000440), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_SEESAW_PLATFORM, bob_geo_000458), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BARS_GRILLS, bob_geo_000470), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bob_area_1),
		WARP_NODE(0xF3, LEVEL_BOB, 0x01, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 50, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(0xE9, LEVEL_BOB, 0x01, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(12, LEVEL_BOB, 2, 12, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -1752, 8095, -8468, 0, -180, 0, (49 << 24) | (102 << 16) | (70 << 8) | (4), bhv2DScene),
		OBJECT(MODEL_NONE, -1747, 1241, 1545, 0, -180, 0, (26 << 24), bhvCheckpointArea),
		OBJECT(MODEL_NONE, 12983, 13070, 14201, -90, -90, 0, (0xE9 << 24) | (0xE9 << 16), bhvAirborneWarp),
		OBJECT(MODEL_WOOD_CRATE, -1749, 1875, -7182, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 1875, -7602, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 1875, -6762, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 2295, -7182, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 2295, -7602, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 2295, -6762, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_IRON_CRATE, -1749, 1451, -3879, 0, 0, 0, 0x00000000, bhvIronCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 2568, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 2988, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 3408, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 3828, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 4248, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 4668, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 5088, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 5508, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 5928, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 6348, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 6768, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_WOOD_CRATE, -1749, 7188, -17763, 0, 0, 0, 0x00000000, bhvWoodCrate),
		OBJECT(MODEL_IRON_CRATE, -1749, 4175, -13809, 0, 0, 0, 0x00000000, bhvIronCrate),
		OBJECT(MODEL_IRON_CRATE, -1749, 8790, -5486, 0, 0, 0, 0x00000000, bhvIronCrate),
		OBJECT(MODEL_IRON_CRATE, -1749, 8276, -11883, 0, 0, 0, 0x00000000, bhvIronCrate),
		OBJECT(MODEL_IRON_CRATE, -1749, 8079, -2272, 0, 0, 0, 0x00000000, bhvIronCrate),
		OBJECT(MODEL_IRON_CRATE, -1749, 7806, -8710, 0, 0, 0, 0x00000000, bhvIronCrate),
		OBJECT(MODEL_WARP_PIPE, -1747, 7679, 2186, -90, 0, 0, (10 << 24) | (12 << 16), bhvWarpPipe),
		OBJECT(MODEL_WARP_PIPE, 6642, 10572, 13709, -90, 0, 0, (10 << 24) | (12 << 16), bhvWarpPipe),
		OBJECT(MODEL_JOHN_PILLAR, 4239, 9991, 14202, 0, 0, 0, 0x00000000, bhvJohnPillar),
		MARIO_POS(0x01, -90, 12983, 13070, 14201),
		OBJECT(MODEL_NONE, 13173, 11451, 14187, 0, -90, 0, (3 << 24) | (2 << 16), bhvSignOnWall),
		TERRAIN(bob_area_1_collision),
		MACRO_OBJECTS(bob_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SPOOKY),
		TERRAIN_TYPE(TERRAIN_SLIDE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, bob_area_2),
		WARP_NODE(0xF3, LEVEL_BOB, 0x02, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x02, 50, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x02, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(0xE9, LEVEL_BOB, 0x02, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(13, LEVEL_BOB, 3, 13, WARP_NO_CHECKPOINT),
		WARP_NODE(12, LEVEL_BOB, 1, 12, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -155, -9721, 5847, 90, 0, 0, (33 << 24) | (105 << 16) | (4 << 8) | (0), bhv2DCylinderScene),
		OBJECT(MODEL_NONE, -20185, 8763, 430, 0, -180, 0, (167 << 24) | (24 << 16) | (94 << 8) | (4), bhv2DScene),
		OBJECT(MODEL_IRON_CAGE, -3125, -2509, 4206, 0, -28, 0, 0x00000000, bhvIronCage),
		OBJECT(MODEL_NONE, -3722, 1409, 5402, 0, 156, 0, (10 << 24), bhvCheckpointArea),
		OBJECT(MODEL_NONE, 18353, -4659, -16887, 0, -90, 0, (20 << 24), bhvCheckpointArea),
		OBJECT(MODEL_NONE, 130, -9165, 12345, -90, 0, 0, (0xE9 << 24) | (0xE9 << 16), bhvAirborneWarp),
		OBJECT(MODEL_WARP_PIPE, -154, -9659, 12914, 0, 0, 0, (10 << 24) | (12 << 16), bhvWarpPipe),
		OBJECT(MODEL_WARP_PIPE, -2510, -5315, -16887, 0, 0, 0, (10 << 24) | (13 << 16), bhvWarpPipe),
		OBJECT(MODEL_WARP_PIPE, 819, -9659, 12798, 0, 0, 0, (10 << 24) | (13 << 16), bhvWarpPipe),
		OBJECT(MODEL_CANNON_BASE, -155, -4233, 8073, 90, 0, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_CANNON_BASE, 2129, -4286, 6174, 90, 90, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_CANNON_BASE, 23, -4887, 3632, 90, 161, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_MR_I, -155, -3996, 5847, 0, 0, 0, (8 << 16), bhvLargeMrI),
		OBJECT(MODEL_PIZZA_FACE, 14904, -9614, 5564, 0, 0, 0, 0x00000000, bhvPizzaFace),
		TERRAIN(bob_area_2_collision),
		MACRO_OBJECTS(bob_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_PIZZA_TIME),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, bob_area_3),
		WARP_NODE(0xF3, LEVEL_BOB, 0x03, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x03, 50, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x03, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(0xE9, LEVEL_BOB, 0x03, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(13, LEVEL_BOB, 2, 13, WARP_NO_CHECKPOINT),
		WARP_NODE(14, LEVEL_BOB, 4, 14, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_IRON_CAGE, -10600, 9617, 9675, 0, -8, 0, 0x00000000, bhvIronCage),
		OBJECT(MODEL_NONE, 27256, 4428, -167, -90, -90, 0, (0xE9 << 24) | (0xE9 << 16), bhvAirborneWarp),
		OBJECT(MODEL_WARP_PIPE, 27907, 3931, -132, 0, 90, 0, (10 << 24) | (13 << 16), bhvWarpPipe),
		OBJECT(MODEL_WARP_PIPE, -18644, 18, 2856, 0, -92, 0, (10 << 24) | (14 << 16), bhvWarpPipe),
		OBJECT(MODEL_ANTI_GRAV_OLIVE, 12375, -1031, -137, 0, 0, 0, 0x00000000, bhvAntiGravOlive),
		OBJECT(MODEL_ANTI_GRAV_OLIVE, 5270, 822, -21084, 0, 0, 0, 0x00000000, bhvAntiGravOlive),
		OBJECT(MODEL_ANTI_GRAV_OLIVE, 23081, 5063, -9836, 0, 0, 0, 0x00000000, bhvAntiGravOlive),
		OBJECT(MODEL_ANTI_GRAV_OLIVE, -1931, 8302, 15215, 0, 0, 0, 0x00000000, bhvAntiGravOlive),
		OBJECT(MODEL_ANTI_GRAV_OLIVE, -13794, -3305, 9877, 0, 0, 0, 0x00000000, bhvAntiGravOlive),
		OBJECT(MODEL_PIZZA_FACE, 29162, 4137, -132, 0, 0, 0, 0x00000000, bhvPizzaFace),
		TERRAIN(bob_area_3_collision),
		MACRO_OBJECTS(bob_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_PIZZA_TIME),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, bob_area_4),
		WARP_NODE(0xF3, LEVEL_BOB, 0x04, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x04, 50, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x04, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(0xE9, LEVEL_BOB, 0x04, 0xE9, WARP_NO_CHECKPOINT),
		WARP_NODE(14, LEVEL_BOB, 3, 14, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 26807, 5372, -167, -90, -90, 0, (0xE9 << 24) | (0xE9 << 16), bhvAirborneWarp),
		OBJECT(MODEL_WARP_PIPE, 27907, 4132, -132, 0, 90, 0, (10 << 24) | (14 << 16), bhvWarpPipe),
		OBJECT(MODEL_NONE, -17271, 4681, -136, 0, 90, 0, 0x00000000, bhvRocketObstacle),
		OBJECT(MODEL_NONE, -2833, 4681, -136, 0, 90, 0, 0x00000000, bhvRocketObstacle),
		OBJECT(MODEL_NONE, 11889, 4681, -136, 0, 90, 0, 0x00000000, bhvRocketObstacle),
		OBJECT(MODEL_PIZZA_FACE, 29162, 4137, -132, 0, 0, 0, 0x00000000, bhvPizzaFace),
		OBJECT(MODEL_ROCKET, 24475, 4569, -137, 0, -90, 0, 0x00000000, bhvRocket),
		TERRAIN(bob_area_4_collision),
		MACRO_OBJECTS(bob_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_PIZZA_TIME),
		TERRAIN_TYPE(TERRAIN_SLIDE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -90, 12983, 13070, 14201),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
