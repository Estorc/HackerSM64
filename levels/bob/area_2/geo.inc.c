#include "src/game/envfx_snow.h"

const GeoLayout bob_area_2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -155, -9721, 5847, bob_dl_Cylinder_mesh_layer_1),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 2439, 1349, 6200, 0, -155, 0, bob_dl_FinalSlide_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -155, -4233, 8008, bob_dl_FlamethrowerSphere_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, bob_dl_FlamethrowerSphere_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 2063, -4286, 6174, 0, 90, 0, bob_dl_FlamethrowerSphere_001_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, bob_dl_FlamethrowerSphere_001_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 2, -4887, 3694, 0, 161, 0, bob_dl_FlamethrowerSphere_002_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, bob_dl_FlamethrowerSphere_002_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, -4168, 23954, -3750, 90, 0, -90, bob_dl_Rope_015_mesh_layer_4),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, 628, 20541, 1610, 90, 0, -90, bob_dl_Rope_016_mesh_layer_4),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, -10881, 24923, 13063, 90, 0, -90, bob_dl_Rope_017_mesh_layer_4),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, -5352, 27534, 7026, 90, 0, -90, bob_dl_Rope_018_mesh_layer_4),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, -17313, 19661, 8267, 90, 0, -90, bob_dl_Rope_019_mesh_layer_4),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, -15508, 25429, 17351, 90, 0, -90, bob_dl_Rope_020_mesh_layer_4),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, -9527, 28159, 19551, 90, 0, -90, bob_dl_Rope_021_mesh_layer_4),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, 1474, 23463, 9960, 90, 0, -90, bob_dl_Rope_022_mesh_layer_4),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_ALPHA, 176, 24817, 17407, 90, 0, -90, bob_dl_Rope_023_mesh_layer_4),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -2350, 478, 4420, bob_dl_Slide2_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -2350, 15495, 3173, bob_dl_Slide3_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_FORCE, -155, 11352, 4908, bob_dl_Wall_001_mesh_layer_0),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -20193, 1544, -1969, bob_dl_WallJump_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 19645, 15877, -16887, bob_dl_WallJump_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout bob_area_2[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(0),
		GEO_OPEN_NODE(),
			GEO_NODE_ORTHO(100.0000),
			GEO_OPEN_NODE(),
				GEO_BACKGROUND_COLOR(0x0001),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 3000000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, -74042, 0, -100, -74042, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, bob_area_2_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_FORCE, bob_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bob_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bob_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};