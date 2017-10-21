			fname, name);
		return NULL;
	}

	if (!datum_len && !extra_len)
		extra_len = 1; /* request non-zero amount of memory */
	if (datum_len + extra_len < datum_len)
		overflow_exit("get_xattr_data");
	if (!(ptr = new_array(char, datum_len + extra_len)))
		out_of_memory("get_xattr_data");

	if (datum_len) {
		size_t len = sys_lgetxattr(fname, name, ptr, datum_len);
		if (len != datum_len) {
			if (len == (size_t)-1) {
