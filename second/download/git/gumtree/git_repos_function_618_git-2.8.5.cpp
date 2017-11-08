const char *current_config_origin_type(void)
{
	return cf && cf->origin_type ? cf->origin_type : "command line";
}