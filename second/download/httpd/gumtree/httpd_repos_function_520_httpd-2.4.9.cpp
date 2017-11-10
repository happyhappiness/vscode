static int magic_rsl_putchar(request_rec *r, char c)
{
    char str[2];

    /* high overhead for 1 char - just hope they don't do this much */
    str[0] = c;
    str[1] = '\0';
    return magic_rsl_add(r, str);
}