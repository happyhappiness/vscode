	} else if (lk->filename.len) {
		/* This shouldn't happen, but better safe than sorry. */
		die("BUG: lock_file(\"%s\") called with improperly-reset lock_file object",
		    path);
	}

	if (flags & LOCK_NO_DEREF) {
		strbuf_add_absolute_path(&lk->filename, path);
	} else {
		struct strbuf resolved_path = STRBUF_INIT;

		strbuf_add(&resolved_path, path, pathlen);
		resolve_symlink(&resolved_path);
		strbuf_add_absolute_path(&lk->filename, resolved_path.buf);
		strbuf_release(&resolved_path);
	}

	strbuf_addstr(&lk->filename, LOCK_SUFFIX);
	lk->fd = open(lk->filename.buf, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (lk->fd < 0) {
		strbuf_reset(&lk->filename);
		return -1;
	}
