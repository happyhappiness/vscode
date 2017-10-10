	default:
		return error("unknown file mode for %s in index", path);
	}

finish:
	if (state->refresh_cache) {
		if (!fstat_done)
			lstat(ce->name, &st);
		fill_stat_cache_info(ce, &st);
	}
	return 0;
}

/*
 * This is like 'lstat()', except it refuses to follow symlinks
