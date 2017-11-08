static int set_header(void *ctx, const char *key, const char *value)
{
    h2_to_h1 *to_h1 = (h2_to_h1*)ctx;
    h2_to_h1_add_header(to_h1, key, strlen(key), value, strlen(value));
    return 1;
}