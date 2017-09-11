		else
			opt_narenas = 1;
	}
	narenas = opt_narenas;
	/*
	 * Make sure that the arenas array can be allocated.  In practice, this
	 * limit is enough to allow the allocator to function, but the ctl
	 * machinery will fail to allocate memory at far lower limits.
	 */
	if (narenas > chunksize / sizeof(arena_t *)) {
		narenas = chunksize / sizeof(arena_t *);
		malloc_printf("<jemalloc>: Reducing narenas to limit (%d)\n",
		    narenas);
	}

	/* Allocate and initialize arenas. */
	arenas = (arena_t **)base_alloc(sizeof(arena_t *) * narenas);
	if (arenas == NULL) {
		malloc_mutex_unlock(&init_lock);
		return (true);
