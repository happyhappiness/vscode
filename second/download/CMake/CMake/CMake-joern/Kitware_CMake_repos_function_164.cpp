static void tls_log_func(int level, const char *str)
{
    fprintf(stderr, "|<%d>| %s", level, str);
}