#include "src/game/envfx_snow.h"

const GeoLayout wood_crate_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wood_crate_particle_mesh_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wood_crate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
