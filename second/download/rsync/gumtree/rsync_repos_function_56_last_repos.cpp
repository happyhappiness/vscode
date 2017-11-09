int unmap_file(struct map_struct *map)
{
	int	ret;

	if (map->p) {
		free(map->p);
		map->p = NULL;
	}
	ret = map->status;
	memset(map, 0, sizeof map[0]);
	free(map);

	return ret;
}