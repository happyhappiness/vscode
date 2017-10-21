

/* This provides functionality somewhat similar to mmap() but using read().
 * It gives sliding window access to a file.  mmap() is not used because of
 * the possibility of another program (such as a mailer) truncating the
 * file thus giving us a SIGBUS. */
struct map_struct *map_file(int fd, OFF_T len, int32 read_size, int32 blk_size)
{
	struct map_struct *map;

	if (!(map = new0(struct map_struct)))
		out_of_memory("map_file");

	if (blk_size && (read_size % blk_size))
		read_size += blk_size - (read_size % blk_size);

	map->fd = fd;
	map->file_size = len;
	map->def_window_size = ALIGNED_LENGTH(read_size);

	return map;
}


/* slide the read window in the file */
char *map_ptr(struct map_struct *map, OFF_T offset, int32 len)
{
	OFF_T window_start, read_start;
	int32 window_size, read_size, read_offset, align_fudge;

	if (len == 0)
		return NULL;
	if (len < 0) {
		rprintf(FERROR, "invalid len passed to map_ptr: %ld\n",
			(long)len);
