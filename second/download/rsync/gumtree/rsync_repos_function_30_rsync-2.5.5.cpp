struct map_struct *map_file(int fd,OFF_T len)
{
	struct map_struct *map;
	map = (struct map_struct *)malloc(sizeof(*map));
	if (!map) out_of_memory("map_file");

	map->fd = fd;
	map->file_size = len;
	map->p = NULL;
	map->p_size = 0;
	map->p_offset = 0;
	map->p_fd_offset = 0;
	map->p_len = 0;

	return map;
}