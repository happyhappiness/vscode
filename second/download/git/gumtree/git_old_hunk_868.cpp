
	dir = opendir(path->buf);
	if (!dir) {
		/* an empty dir could be removed even if it is unreadble */
		res = dry_run ? 0 : rmdir(path->buf);
		if (res) {
			quote_path_relative(path->buf, prefix, &quoted);
			warning(_(msg_warn_remove_failed), quoted.buf);
			*dir_gone = 0;
		}
		return res;
	}

	strbuf_complete(path, '/');
