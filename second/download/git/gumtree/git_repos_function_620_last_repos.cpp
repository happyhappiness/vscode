static long config_file_ftell(struct config_source *conf)
{
	return ftell(conf->u.file);
}