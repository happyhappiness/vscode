int check_leading_path(const char *name, int len)
{
    return threaded_check_leading_path(&default_cache, name, len);
}