static int config_file_fgetc(struct config_source *conf)
{
	return getc_unlocked(conf->u.file);
}