static char *find_closing_bracket(char *s, int left, int right)
{
    int depth;

    for (depth = 1; *s; ++s) {
        if (*s == right && --depth == 0) {
            return s;
        }
        else if (*s == left) {
            ++depth;
        }
    }
    return NULL;
}