static long config_buf_ftell(struct config_source *conf)
{
	return conf->u.buf.pos;
}