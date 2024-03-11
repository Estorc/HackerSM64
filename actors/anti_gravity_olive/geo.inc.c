#include "src/game/envfx_snow.h"

const GeoLayout anti_gravity_olive_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SCALE(LAYER_TRANSPARENT, 65536),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_update_layer_transparency),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, anti_gravity_olive_002_display_list_mesh_layer_5),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, anti_gravity_olive_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
