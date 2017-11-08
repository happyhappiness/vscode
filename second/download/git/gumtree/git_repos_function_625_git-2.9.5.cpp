const char *current_config_name(void)
{
	return cf && cf->name ? cf->name : "";
}