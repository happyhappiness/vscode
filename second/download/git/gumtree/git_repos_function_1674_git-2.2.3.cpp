int for_each_loose_file_in_objdir(const char *path,
			    each_loose_object_fn obj_cb,
			    each_loose_cruft_fn cruft_cb,
			    each_loose_subdir_fn subdir_cb,
			    void *data)
{
	struct strbuf buf = STRBUF_INIT;
	size_t baselen;
	int r = 0;
	int i;

	strbuf_addstr(&buf, path);
	strbuf_addch(&buf, '/');
	baselen = buf.len;

	for (i = 0; i < 256; i++) {
		strbuf_addf(&buf, "%02x", i);
		r = for_each_file_in_obj_subdir(i, &buf, obj_cb, cruft_cb,
						subdir_cb, data);
		strbuf_setlen(&buf, baselen);
		if (r)
			break;
	}

	strbuf_release(&buf);
	return r;
}