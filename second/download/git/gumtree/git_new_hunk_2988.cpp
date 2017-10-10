
	matched_src = matched_dst = NULL;
	if (match_explicit_lhs(src, rs, &matched_src, &allocated_src) < 0)
		return -1;

	if (!dst_value) {
		struct object_id oid;
		int flag;

		dst_value = resolve_ref_unsafe(matched_src->name,
					       RESOLVE_REF_READING,
					       oid.hash, &flag);
		if (!dst_value ||
		    ((flag & REF_ISSYMREF) &&
		     !starts_with(dst_value, "refs/heads/")))
			die("%s cannot be resolved to branch.",
			    matched_src->name);
	}
