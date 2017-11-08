static inline int pthread_key_delete(pthread_key_t key)
{
	return TlsFree(key) ? 0 : EINVAL;
}