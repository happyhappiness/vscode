static int batch_objects(struct batch_options *opt)
{
	struct strbuf buf = STRBUF_INIT;
	struct expand_data data;
	int save_warning;
	int retval = 0;

	if (!opt->format)
		opt->format = "%(objectname) %(objecttype) %(objectsize)";

	/*
	 * Expand once with our special mark_query flag, which will prime the
	 * object_info to be handed to sha1_object_info_extended for each
	 * object.
	 */
	memset(&data, 0, sizeof(data));
	data.mark_query = 1;
	strbuf_expand(&buf, opt->format, expand_format, &data);
	data.mark_query = 0;
	if (opt->cmdmode)
		data.split_on_whitespace = 1;

	if (opt->all_objects) {
		struct object_info empty = OBJECT_INFO_INIT;
		if (!memcmp(&data.info, &empty, sizeof(empty)))
			data.skip_object_info = 1;
	}

	/*
	 * If we are printing out the object, then always fill in the type,
	 * since we will want to decide whether or not to stream.
	 */
	if (opt->print_contents)
		data.info.typep = &data.type;

	if (opt->all_objects) {
		struct oid_array sa = OID_ARRAY_INIT;
		struct object_cb_data cb;

		for_each_loose_object(batch_loose_object, &sa, 0);
		for_each_packed_object(batch_packed_object, &sa, 0);

		cb.opt = opt;
		cb.expand = &data;
		oid_array_for_each_unique(&sa, batch_object_cb, &cb);

		oid_array_clear(&sa);
		return 0;
	}

	/*
	 * We are going to call get_sha1 on a potentially very large number of
	 * objects. In most large cases, these will be actual object sha1s. The
	 * cost to double-check that each one is not also a ref (just so we can
	 * warn) ends up dwarfing the actual cost of the object lookups
	 * themselves. We can work around it by just turning off the warning.
	 */
	save_warning = warn_on_object_refname_ambiguity;
	warn_on_object_refname_ambiguity = 0;

	while (strbuf_getline(&buf, stdin) != EOF) {
		if (data.split_on_whitespace) {
			/*
			 * Split at first whitespace, tying off the beginning
			 * of the string and saving the remainder (or NULL) in
			 * data.rest.
			 */
			char *p = strpbrk(buf.buf, " \t");
			if (p) {
				while (*p && strchr(" \t", *p))
					*p++ = '\0';
			}
			data.rest = p;
		}

		batch_one_object(buf.buf, opt, &data);
	}

	strbuf_release(&buf);
	warn_on_object_refname_ambiguity = save_warning;
	return retval;
}