
	return EOF;
}

static int config_buf_ungetc(int c, struct config_source *conf)
{
	if (conf->u.buf.pos > 0) {
		conf->u.buf.pos--;
		if (conf->u.buf.buf[conf->u.buf.pos] != c)
			die("BUG: config_buf can only ungetc the same character");
		return c;
	}

	return EOF;
}

static long config_buf_ftell(struct config_source *conf)
{
