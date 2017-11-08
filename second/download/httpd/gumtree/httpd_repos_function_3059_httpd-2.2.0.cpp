void add_rpath_noinstall(count_chars *cc, const char *arg, int pathlen)
{
    const char *path;

    path = load_noinstall_path(arg, pathlen);
    if (path) {
        add_rpath(cc, path);
    }
}