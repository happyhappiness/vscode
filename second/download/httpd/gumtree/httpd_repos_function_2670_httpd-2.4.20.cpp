static unsigned int stream_hash(const char *key, apr_ssize_t *klen)
{
    return (unsigned int)(*((int*)key));
}