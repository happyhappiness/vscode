

/* This provides functionality somewhat similar to mmap() but using read().
 * It gives sliding window access to a file.  mmap() is not used because of
 * the possibility of another program (such as a mailer) truncating the
 * file thus giving us a SIGBUS. */
struct map_struct *map_file(int fd, OFF_T len, OFF_T map_size,
			    size_t block_size)
{
	struct map_struct *map;

	if (!(map = new(struct map_struct)))
		out_of_memory("map_file");

	if (block_size && (map_size % block_size))
		map_size += block_size - (map_size % block_size);

	memset(map, 0, sizeof map[0]);
	map->fd = fd;
	map->file_size = len;
	map->def_window_size = map_size;

	return map;
}


/* slide the read window in the file */
char *map_ptr(struct map_struct *map,OFF_T offset,int len)
{
	int nread;
	OFF_T window_start, read_start;
	int window_size, read_size, read_offset;

	if (len == 0)
		return NULL;

	/* can't go beyond the end of file */
	if (len > (map->file_size - offset)) {
		len = map->file_size - offset;
	}

	/* in most cases the region will already be available */
	if (offset >= map->p_offset &&
	    offset+len <= map->p_offset+map->p_len) {
		return (map->p + (offset - map->p_offset));
	}

	/* nope, we are going to have to do a read. Work out our desired window */
	window_start = offset;
	window_size = map->def_window_size;
	if (window_start + window_size > map->file_size) {
		window_size = map->file_size - window_start;
	}
	if (offset + len > window_start + window_size) {
		window_size = (offset+len) - window_start;
	}

	/* make sure we have allocated enough memory for the window */
	if (window_size > map->p_size) {
		map->p = realloc_array(map->p, char, window_size);
		if (!map->p)
			out_of_memory("map_ptr");
		map->p_size = window_size;
	}

	/* now try to avoid re-reading any bytes by reusing any bytes from the previous
	   buffer. */
	if (window_start >= map->p_offset &&
	    window_start < map->p_offset + map->p_len &&
	    window_start + window_size >= map->p_offset + map->p_len) {
		read_start = map->p_offset + map->p_len;
		read_offset = read_start - window_start;
		read_size = window_size - read_offset;
