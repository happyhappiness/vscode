static inline void hashmap_unlock(struct attr_hashmap *map)
{
#ifndef NO_PTHREADS
	pthread_mutex_unlock(&map->mutex);
#endif
}