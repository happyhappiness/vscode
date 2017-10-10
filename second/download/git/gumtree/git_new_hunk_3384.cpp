			goto deleted_file;

		if (S_ISLNK(st.st_mode)) {
			struct strbuf buf = STRBUF_INIT;

			if (strbuf_readlink(&buf, elem->path, st.st_size) < 0) {
				error_errno("readlink(%s)", elem->path);
				return;
			}
			result_size = buf.len;
			result = strbuf_detach(&buf, NULL);
			elem->mode = canon_mode(st.st_mode);
		} else if (S_ISDIR(st.st_mode)) {
