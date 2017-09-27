    expanded_path = newarg;
#endif

    return expanded_path;
}

/* Read the final install location and add it to runtime library search path. */
#ifdef RPATH
void add_rpath(count_chars *cc, const char *path)
{
    int size = 0;
    char *tmp;
