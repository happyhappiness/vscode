static inline int pthread_key_create(pthread_key_t *keyp, void (*destructor)(void *value))
{
	return (*keyp = TlsAlloc()) == TLS_OUT_OF_INDEXES ? EAGAIN : 0;
}