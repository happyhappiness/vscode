static inline void *pthread_getspecific(pthread_key_t key)
{
	return TlsGetValue(key);
}