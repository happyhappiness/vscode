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
		fflush(stdout);
		return 0;
	}

	strbuf_expand(&buf, opt->format, expand_format, data);
	strbuf_addch(&buf, '\n');
	write_or_die(1, buf.buf, buf.len);
	strbuf_release(&buf);

	if (opt->print_contents) {
		print_object_or_die(1, data);
		write_or_die(1, "\n", 1);
	}
	return 0;
}