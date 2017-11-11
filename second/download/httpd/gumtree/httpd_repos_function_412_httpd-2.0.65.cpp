static int count_string(const char *p)
{
    int n;

    for (n = 0 ; *p ; ++p, ++n)
        if (test_char_table[*(unsigned char *)p]&T_ESCAPE_FORENSIC)
            n += 2;
    return n;
}