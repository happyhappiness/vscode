			die("object %s disappeared", sha1_to_hex(sha1));
		if (type != data->type)
			die("object %s changed type!?", sha1_to_hex(sha1));
		if (data->info.sizep && size != data->size)
			die("object %s changed size!?", sha1_to_hex(sha1));

		write_or_die(fd, contents, size);
		free(contents);
	}
}

struct batch_options {
	int enabled;
	int follow_symlinks;
	int print_contents;
	const char *format;
};

static int batch_one_object(const char *obj_name, struct batch_options *opt,
			    struct expand_data *data)
{
	struct strbuf buf = STRBUF_INIT;
	struct object_context ctx;
	int flags = opt->follow_symlinks ? GET_SHA1_FOLLOW_SYMLINKS : 0;
	enum follow_symlinks_result result;

	if (!obj_name)
	   return 1;

	result = get_sha1_with_context(obj_name, flags, data->sha1, &ctx);
	if (result != FOUND) {
		switch (result) {
		case MISSING_OBJECT:
			printf("%s missing\n", obj_name);
			break;
