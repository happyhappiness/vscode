int get_fetch_map(const struct ref *remote_refs,
		  const struct refspec *refspec,
		  struct ref ***tail,
		  int missing_ok)
{
	struct ref *ref_map, **rmp;

	if (refspec->pattern) {
		ref_map = get_expanded_map(remote_refs, refspec);
	} else {
		const char *name = refspec->src[0] ? refspec->src : "HEAD";

		if (refspec->exact_sha1) {
			ref_map = alloc_ref(name);
			get_oid_hex(name, &ref_map->old_oid);
		} else {
			ref_map = get_remote_ref(remote_refs, name);
		}
		if (!missing_ok && !ref_map)
			die("Couldn't find remote ref %s", name);
		if (ref_map) {
			ref_map->peer_ref = get_local_ref(refspec->dst);
			if (ref_map->peer_ref && refspec->force)
				ref_map->peer_ref->force = 1;
		}
	}

	for (rmp = &ref_map; *rmp; ) {
		if ((*rmp)->peer_ref) {
			if (!starts_with((*rmp)->peer_ref->name, "refs/") ||
			    check_refname_format((*rmp)->peer_ref->name, 0)) {
				struct ref *ignore = *rmp;
				error("* Ignoring funny ref '%s' locally",
				      (*rmp)->peer_ref->name);
				*rmp = (*rmp)->next;
				free(ignore->peer_ref);
				free(ignore);
				continue;
			}
		}
		rmp = &((*rmp)->next);
	}

	if (ref_map)
		tail_link_ref(ref_map, tail);

	return 0;
}