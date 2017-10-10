static void batch_object_write(const char *obj_name, struct batch_options *opt,
			       struct expand_data *data)
{
	struct strbuf buf = STRBUF_INIT;

	if (!data->skip_object_info &&
	    sha1_object_info_extended(data->oid.hash, &data->info,
				      OBJECT_INFO_LOOKUP_REPLACE) < 0) {
		printf("%s missing\n",
		       obj_name ? obj_name : oid_to_hex(&data->oid));
		fflush(stdout);
		return;
	}

