#include "src/game/envfx_snow.h"

const GeoLayout star_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(0, 155, 100),
		GEO_OPEN_NODE(),
			GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_TRANSPARENT, 0, 0, 0, star_000_billboard_mesh_layer_5),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, star_000_displaylist_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_ALPHA, star_001_displaylist_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, star_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, star_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
