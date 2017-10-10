
	return 0;
}

const char *current_config_origin_type(void)
{
	return cf && cf->origin_type ? cf->origin_type : "command line";
}

const char *current_config_name(void)
{
	return cf && cf->name ? cf->name : "";
}
