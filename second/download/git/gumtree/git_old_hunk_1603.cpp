		return error(_("path %s has been renamed/deleted"),
			     patch->old_name);
	if (previous) {
		/* We have a patched copy in memory; use that. */
		strbuf_add(&buf, previous->result, previous->resultsize);
	} else {
		status = load_patch_target(state, &buf, ce, st,
					   patch->old_name, patch->old_mode);
		if (status < 0)
			return status;
		else if (status == SUBMODULE_PATCH_WITHOUT_INDEX) {
			/*
			 * There is no way to apply subproject
