static int do_config_from_file(config_fn_t fn,
		const char *origin_type, const char *name, const char *path, FILE *f,
		void *data)
{
	struct config_source top;

	top.u.file = f;
	top.origin_type = origin_type;
	top.name = name;
	top.path = path;
	top.die_on_error = 1;
	top.do_fgetc = config_file_fgetc;
	top.do_ungetc = config_file_ungetc;
	top.do_ftell = config_file_ftell;

	return do_config_from(&top, fn, data);
}