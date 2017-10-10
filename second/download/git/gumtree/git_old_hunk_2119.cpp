
	return EOF;
}

static int config_buf_ungetc(int c, struct config_source *conf)
{
	if (conf->u.buf.pos > 0)
		return conf->u.buf.buf[--conf->u.buf.pos];

	return EOF;
}

static long config_buf_ftell(struct config_source *conf)
{
