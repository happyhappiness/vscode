	output[17] = (unsigned char)(ctx->ihv[4] >> 16);
	output[18] = (unsigned char)(ctx->ihv[4] >> 8);
	output[19] = (unsigned char)(ctx->ihv[4]);
	return ctx->found_collision;
}

#ifdef SHA1DC_CUSTOM_TRAILING_INCLUDE_SHA1_C
#include SHA1DC_CUSTOM_TRAILING_INCLUDE_SHA1_C
#endif
