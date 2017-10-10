		ret = error("reflog for %s is a symlink", oldrefname);
		goto out;
	}

	if (!refs_resolve_ref_unsafe(&refs->base, oldrefname,
				     RESOLVE_REF_READING | RESOLVE_REF_NO_RECURSE,
				orig_oid.hash, &flag)) {
		ret = error("refname %s not found", oldrefname);
		goto out;
	}

	if (flag & REF_ISSYMREF) {
		ret = error("refname %s is a symbolic ref, renaming it is not supported",
