void safe_mkdir(const char *path)
{
    mode_t old_umask;

    old_umask = umask(0);
    umask(old_umask);

#ifdef MKDIR_NO_UMASK
    mkdir(path);
#else
    mkdir(path, ~old_umask);
#endif
}