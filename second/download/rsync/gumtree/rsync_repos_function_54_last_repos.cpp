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