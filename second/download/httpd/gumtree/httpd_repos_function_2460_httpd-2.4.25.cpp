static unsigned int val_apr_hash(const char *str) 
{
    apr_ssize_t len = strlen(str);
    return apr_hashfunc_default(str, &len);
}