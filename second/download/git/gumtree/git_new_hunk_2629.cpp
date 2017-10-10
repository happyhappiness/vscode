		goto rollback;
	}

	if (!read_ref_full(newrefname, RESOLVE_REF_READING, sha1, NULL) &&
	    delete_ref(newrefname, sha1, REF_NODEREF)) {
		if (errno==EISDIR) {
			struct strbuf path = STRBUF_INIT;
			int result;

			strbuf_git_path(&path, "%s", newrefname);
			result = remove_empty_directories(&path);
			strbuf_release(&path);

			if (result) {
				error("Directory not empty: %s", newrefname);
				goto rollback;
			}
		} else {
			error("unable to delete existing %s", newrefname);
			goto rollback;
