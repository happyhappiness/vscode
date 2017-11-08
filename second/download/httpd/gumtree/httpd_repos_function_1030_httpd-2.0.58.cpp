static char *find_char_in_brackets(char *s, int c, int left, int right)
{
    int depth;

    for (depth = 1; *s; ++s) {
        if (*s == c && depth == 1) {
            return s;
        }
        else if (*s == right && --depth == 0) {
            return NULL;
        }
        else if (*s == left) {
            ++depth;
        }
    }
    return NULL;
}