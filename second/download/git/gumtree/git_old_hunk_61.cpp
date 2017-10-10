		if (!ce)
			die(_("make_cache_entry failed for path '%s'"), name);
		if (add_index_entry(&result, ce, ADD_CACHE_OK_TO_ADD))
			die ("Could not add %s to temporary index", name);
	}

	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0 || write_index(&result, fd) || close(fd))
		die ("Could not write temporary index to %s", filename);

	discard_index(&result);
}

static void stat_patch_list(struct patch *patch)
