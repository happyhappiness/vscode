static void
init_syntax_once(void)
{
    register int c;
    static int done = 0;

    if (done)
        return;

    memset(re_syntax_table, 0, sizeof re_syntax_table);

    for (c = 'a'; c <= 'z'; c++)
        re_syntax_table[c] = Sword;

    for (c = 'A'; c <= 'Z'; c++)
        re_syntax_table[c] = Sword;

    for (c = '0'; c <= '9'; c++)
        re_syntax_table[c] = Sword;

    re_syntax_table['_'] = Sword;

    done = 1;
}