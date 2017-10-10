		free(contents);
	}
}

struct batch_options {
	int enabled;
	int print_contents;
	const char *format;
};

static int batch_one_object(const char *obj_name, struct batch_options *opt,
			    struct expand_data *data)
{
	struct strbuf buf = STRBUF_INIT;

	if (!obj_name)
	   return 1;

	if (get_sha1(obj_name, data->sha1)) {
		printf("%s missing\n", obj_name);
		fflush(stdout);
		return 0;
	}

	if (sha1_object_info_extended(data->sha1, &data->info, LOOKUP_REPLACE_OBJECT) < 0) {
		printf("%s missing\n", obj_name);
