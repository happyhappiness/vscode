int git_config_from_mem(config_fn_t fn, const enum config_origin_type origin_type,
			const char *name, const char *buf, size_t len, void *data)
{
	struct config_source top;

	top.u.buf.buf = buf;
	top.u.buf.len = len;
	top.u.buf.pos = 0;
	top.origin_type = origin_type;
	top.name = name;
	top.path = NULL;
	top.die_on_error = 0;
	top.do_fgetc = config_buf_fgetc;
	top.do_ungetc = config_buf_ungetc;
	top.do_ftell = config_buf_ftell;

	return do_config_from(&top, fn, data);
}