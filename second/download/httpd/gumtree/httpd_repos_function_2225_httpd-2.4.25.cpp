static unsigned int ihash(const char *key, apr_ssize_t *klen)
{
    return (unsigned int)(*((int*)key));
}