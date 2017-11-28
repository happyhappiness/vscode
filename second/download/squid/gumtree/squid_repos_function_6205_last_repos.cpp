int
logfile_mod_stdio_open(Logfile * lf, const char *path, size_t bufsz, int fatal_flag)
{
    lf->f_close = logfile_mod_stdio_close;
    lf->f_linewrite = logfile_mod_stdio_writeline;
    lf->f_linestart = logfile_mod_stdio_linestart;
    lf->f_lineend = logfile_mod_stdio_lineend;
    lf->f_flush = logfile_mod_stdio_flush;
    lf->f_rotate = logfile_mod_stdio_rotate;

    l_stdio_t *ll = static_cast<l_stdio_t*>(xcalloc(1, sizeof(*ll)));
    lf->data = ll;

    ll->fd = file_open(path, O_WRONLY | O_CREAT | O_TEXT);

    if (DISK_ERROR == ll->fd) {
        int xerrno = errno;
        if (ENOENT == xerrno && fatal_flag) {
            fatalf("Cannot open '%s' because\n"
                   "\tthe parent directory does not exist.\n"
                   "\tPlease create the directory.\n", path);
        } else if (EACCES == xerrno && fatal_flag) {
            fatalf("Cannot open '%s' for writing.\n"
                   "\tThe parent directory must be writeable by the\n"
                   "\tuser '%s', which is the cache_effective_user\n"
                   "\tset in squid.conf.", path, Config.effectiveUser);
        } else if (EISDIR == xerrno && fatal_flag) {
            fatalf("Cannot open '%s' because it is a directory, not a file.\n", path);
        } else {
            debugs(50, DBG_IMPORTANT, MYNAME << "ERROR: " << lf->path << ": " << xstrerr(xerrno));
            return 0;
        }
    }
    if (bufsz > 0) {
        ll->buf = static_cast<char*>(xmalloc(bufsz));
        ll->bufsz = bufsz;
    }
    return 1;
}