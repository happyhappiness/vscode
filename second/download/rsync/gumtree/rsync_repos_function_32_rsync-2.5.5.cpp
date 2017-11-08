void unmap_file(struct map_struct *map)
{
	if (map->p) {
		free(map->p);
		map->p = NULL;
	}
	memset(map, 0, sizeof(*map));
	free(map);
}