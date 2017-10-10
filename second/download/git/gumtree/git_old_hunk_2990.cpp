		ref_map = get_expanded_map(remote_refs, refspec);
	} else {
		const char *name = refspec->src[0] ? refspec->src : "HEAD";

		if (refspec->exact_sha1) {
			ref_map = alloc_ref(name);
			get_sha1_hex(name, ref_map->old_sha1);
		} else {
			ref_map = get_remote_ref(remote_refs, name);
		}
		if (!missing_ok && !ref_map)
			die("Couldn't find remote ref %s", name);
		if (ref_map) {
