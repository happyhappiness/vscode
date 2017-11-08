int for_each_loose_file_in_objdir_buf(struct strbuf *path,
			    each_loose_object_fn obj_cb,
			    each_loose_cruft_fn cruft_cb,
			    each_loose_subdir_fn subdir_cb,
			    void *data)
{
	size_t baselen = path->len;
	int r = 0;
	int i;

	for (i = 0; i < 256; i++) {
		strbuf_addf(path, "/%02x", i);
		r = for_each_file_in_obj_subdir(i, path, obj_cb, cruft_cb,
						subdir_cb, data);
		strbuf_setlen(path, baselen);
		if (r)
			break;
	}

	return r;
}