		new_ce->ce_flags = create_ce_flags(0) | CE_CONFLICTED;
		new_ce->ce_namelen = len;
		new_ce->ce_mode = ce->ce_mode;
		if (add_index_entry(istate, new_ce, 0))
			return error("%s: cannot drop to stage #0",
				     new_ce->name);
	}
	return unmerged;
}

/*
 * Returns 1 if the path is an "other" path with respect to
