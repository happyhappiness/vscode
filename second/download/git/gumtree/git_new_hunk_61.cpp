		if (!ce)
			die(_("make_cache_entry failed for path '%s'"), name);
		if (add_index_entry(&result, ce, ADD_CACHE_OK_TO_ADD))
			die ("Could not add %s to temporary index", name);
	}

	hold_lock_file_for_update(&lock, filename, LOCK_DIE_ON_ERROR);
	if (write_locked_index(&result, &lock, COMMIT_LOCK))
		die ("Could not write temporary index to %s", filename);

	discard_index(&result);
}

static void stat_patch_list(struct patch *patch)
