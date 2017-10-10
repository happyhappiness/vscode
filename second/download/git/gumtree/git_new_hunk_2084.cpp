	was_same = (alias &&
		    !ce_stage(alias) &&
		    !hashcmp(alias->sha1, ce->sha1) &&
		    ce->ce_mode == alias->ce_mode);

	if (pretend)
		free(ce);
	else if (add_index_entry(istate, ce, add_option)) {
		free(ce);
		return error("unable to add %s to index", path);
	}
	if (verbose && !was_same)
		printf("add '%s'\n", path);
	return 0;
}

int add_file_to_index(struct index_state *istate, const char *path, int flags)
