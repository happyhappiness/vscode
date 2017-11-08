int hashmap_bucket(const struct hashmap *map, unsigned int hash)
{
	return hash & (map->tablesize - 1);
}