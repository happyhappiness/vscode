		return -1;

	if (!dst_value) {
		unsigned char sha1[20];
		int flag;

		dst_value = resolve_ref_unsafe(matched_src->name, sha1, 1, &flag);
		if (!dst_value ||
		    ((flag & REF_ISSYMREF) &&
		     !starts_with(dst_value, "refs/heads/")))
			die("%s cannot be resolved to branch.",
			    matched_src->name);
	}
