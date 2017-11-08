static int identity_count(int *count, const char *key, const char *val)
{
    *count += strlen(key) * 3 + strlen(val) * 3 + 1;
    return 1;
}