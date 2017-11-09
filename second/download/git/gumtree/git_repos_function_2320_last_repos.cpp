static inline void hashmap_lock(struct attr_hashmap *map)
{
#ifndef NO_PTHREADS
	pthread_mutex_lock(&map->mutex);
#endif
}