char *map_ptr(struct map_struct *map, OFF_T offset, int32 len)
{
	OFF_T window_start, read_start;
	int32 window_size, read_size, read_offset, align_fudge;

	if (len == 0)
		return NULL;
	if (len < 0) {
		rprintf(FERROR, "invalid len passed to map_ptr: %ld\n",
			(long)len);
		exit_cleanup(RERR_FILEIO);
	}

	/* in most cases the region will already be available */
	if (offset >= map->p_offset && offset+len <= map->p_offset+map->p_len)
		return map->p + (offset - map->p_offset);

	/* nope, we are going to have to do a read. Work out our desired window */
	align_fudge = (int32)ALIGNED_OVERSHOOT(offset);
	window_start = offset - align_fudge;
	window_size = map->def_window_size;
	if (window_start + window_size > map->file_size)
		window_size = (int32)(map->file_size - window_start);
	if (window_size < len + align_fudge)
		window_size = ALIGNED_LENGTH(len + align_fudge);

	/* make sure we have allocated enough memory for the window */
	if (window_size > map->p_size) {
		map->p = realloc_array(map->p, char, window_size);
		if (!map->p)
			out_of_memory("map_ptr");
		map->p_size = window_size;
	}

	/* Now try to avoid re-reading any bytes by reusing any bytes from the previous buffer. */
	if (window_start >= map->p_offset && window_start < map->p_offset + map->p_len
	 && window_start + window_size >= map->p_offset + map->p_len) {
		read_start = map->p_offset + map->p_len;
		read_offset = (int32)(read_start - window_start);
		read_size = window_size - read_offset;
		memmove(map->p, map->p + (map->p_len - read_offset), read_offset);
	} else {
		read_start = window_start;
		read_size = window_size;
		read_offset = 0;
	}

	if (read_size <= 0) {
		rprintf(FERROR, "invalid read_size of %ld in map_ptr\n",
			(long)read_size);
		exit_cleanup(RERR_FILEIO);
	}

	if (map->p_fd_offset != read_start) {
		OFF_T ret = do_lseek(map->fd, read_start, SEEK_SET);
		if (ret != read_start) {
			rsyserr(FERROR, errno, "lseek returned %s, not %s",
				big_num(ret), big_num(read_start));
			exit_cleanup(RERR_FILEIO);
		}
		map->p_fd_offset = read_start;
	}
	map->p_offset = window_start;
	map->p_len = window_size;

	while (read_size > 0) {
		int32 nread = read(map->fd, map->p + read_offset, read_size);
		if (nread <= 0) {
			if (!map->status)
				map->status = nread ? errno : ENODATA;
			/* The best we can do is zero the buffer -- the file
			 * has changed mid transfer! */
			memset(map->p + read_offset, 0, read_size);
			break;
		}
		map->p_fd_offset += nread;
		read_offset += nread;
		read_size -= nread;
	}

	return map->p + align_fudge;
}