	if (offset + len > window_start + window_size) {
		window_size = (offset+len) - window_start;
	}

	/* make sure we have allocated enough memory for the window */
	if (window_size > map->p_size) {
		map->p = realloc_array(map->p, char, window_size);
		if (!map->p) out_of_memory("map_ptr");
		map->p_size = window_size;
	}

	/* now try to avoid re-reading any bytes by reusing any bytes from the previous
	   buffer. */
