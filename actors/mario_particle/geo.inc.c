#include "src/game/envfx_snow.h"

const GeoLayout mario_particle_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_render_dashing_mario),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
