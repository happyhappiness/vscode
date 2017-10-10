	} else if (is_null_oid(oid)) {
		/* deleted blob */
		*size = 0;
		return xcalloc(1, 1);
	} else if (textconv) {
		struct diff_filespec *df = alloc_filespec(path);
		fill_filespec(df, oid->hash, 1, mode);
		*size = fill_textconv(textconv, df, &blob);
		free_filespec(df);
	} else {
		blob = read_sha1_file(oid->hash, &type, size);
		if (type != OBJ_BLOB)
			die("object '%s' is not a blob!", oid_to_hex(oid));
