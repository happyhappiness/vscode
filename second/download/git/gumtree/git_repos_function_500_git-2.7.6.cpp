static int config_file_ungetc(int c, struct config_source *conf)
{
	return ungetc(c, conf->u.file);
}