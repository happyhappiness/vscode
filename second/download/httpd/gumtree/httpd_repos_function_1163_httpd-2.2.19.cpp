static APR_INLINE char *find_closing_curly(char *s)
{
    unsigned depth;

    for (depth = 1; *s; ++s) {
        if (*s == RIGHT_CURLY && --depth == 0) {
            return s;
        }
        else if (*s == LEFT_CURLY) {
            ++depth;
        }
    }

    return NULL;
}