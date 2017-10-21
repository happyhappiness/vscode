
	/* in most cases the region will already be available */
	if (offset >= map->p_offset && offset+len <= map->p_offset+map->p_len)
		return map->p + (offset - map->p_offset);

	/* nope, we are going to have to do a read. Work out our desired window */
	window_start = offset;
	window_size = map->def_window_size;
	if (window_start + window_size > map->file_size)
		window_size = (int32)(map->file_size - window_start);
	if (len > window_size)
		window_size = len;

	/* make sure we have allocated enough memory for the window */
	if (window_size > map->p_size) {
		map->p = realloc_array(map->p, char, window_size);
		if (!map->p)
			out_of_memory("map_ptr");
		map->p_size = window_size;
	}

	/* Now try to avoid re-reading any bytes by reusing any bytes
	 * from the previous buffer. */
	if (window_start >= map->p_offset &&
	    window_start < map->p_offset + map->p_len &&
	    window_start + window_size >= map->p_offset + map->p_len) {
		read_start = map->p_offset + map->p_len;
		read_offset = (int32)(read_start - window_start);
		read_size = window_size - read_offset;
		memmove(map->p, map->p + (map->p_len - read_offset), read_offset);
	} else {
		read_start = window_start;
