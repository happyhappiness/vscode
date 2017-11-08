static int magic_rsl_puts(request_rec *r, char *str)
{
    return magic_rsl_add(r, str);
}