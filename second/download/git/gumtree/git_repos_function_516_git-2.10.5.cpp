static int config_buf_fgetc(struct config_source *conf)
{
	if (conf->u.buf.pos < conf->u.buf.len)
		return conf->u.buf.buf[conf->u.buf.pos++];

	return EOF;
}