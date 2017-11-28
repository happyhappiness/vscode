size_t
xcountws(const char *str)
{
    size_t count = 0;
    PROF_start(xcountws);

    if (str) {
        while (xisspace(*str)) {
            str++;
            count++;
        }
    }

    PROF_stop(xcountws);
    return count;
}