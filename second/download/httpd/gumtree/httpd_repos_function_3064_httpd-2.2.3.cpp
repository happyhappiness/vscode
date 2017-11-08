void add_rpath_file(count_chars *cc, const char *arg)
{
    const char *path;

    path = load_install_path(arg);
    if (path) {
        add_rpath(cc, path);
    }
}