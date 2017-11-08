void unmap_file(struct map_struct *map)
{
#ifdef USE_MMAP
	if (map->map) {
		munmap(map->map,map->p_len);
		map->map = NULL;
	}
#endif
	if (map->p) {
		free(map->p);
		map->p = NULL;
	}
	memset(map, 0, sizeof(*map));
	free(map);
}