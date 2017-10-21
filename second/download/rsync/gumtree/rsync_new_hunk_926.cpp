		char *ptr, *name;
		rsync_xa *rxa;
		size_t name_len = read_varint(f);
		size_t datum_len = read_varint(f);
		size_t dget_len = datum_len > MAX_FULL_DATUM ? 1 + MAX_DIGEST_LEN : datum_len;
		size_t extra_len = MIGHT_NEED_RPRE ? RPRE_LEN : 0;
		if ((dget_len + extra_len < dget_len)
		 || (dget_len + extra_len + name_len < dget_len))
			overflow_exit("receive_xattr");
		ptr = new_array(char, dget_len + extra_len + name_len);
		if (!ptr)
			out_of_memory("receive_xattr");
		name = ptr + dget_len + extra_len;
		read_buf(f, name, name_len);
		if (dget_len == datum_len)
