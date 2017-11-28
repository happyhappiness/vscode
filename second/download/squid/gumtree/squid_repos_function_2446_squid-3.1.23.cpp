Logfile *
logfileOpen(const char *path, size_t bufsz, int fatal_flag)
{
    int fd;
    Logfile *lf = static_cast<Logfile *>(xcalloc(1, sizeof(*lf)));

    xstrncpy(lf->path, path, MAXPATHLEN);

#if HAVE_SYSLOG

    if (strncmp(path, "syslog", 6) == 0) {
        lf->flags.syslog = 1;
        lf->syslog_priority = LOG_INFO;
        lf->fd = -1;

        if (path[6] != '\0') {
            path += 7;
            char *priority = xstrdup(path);
            char *facility = (char *) strchr(priority, '.');
            if (!facility)
                facility = (char *) strchr(priority, '|');
            if (facility) {
                *facility++ = '\0';
                lf->syslog_priority |= syslog_ntoa(facility);
            }
            lf->syslog_priority |= syslog_ntoa(priority);
            xfree(priority);
            if (0 == (lf->syslog_priority & PRIORITY_MASK))
                lf->syslog_priority |= LOG_INFO;
        }
    } else
#endif
    {
        fd = file_open(path, O_WRONLY | O_CREAT | O_TEXT);

        if (DISK_ERROR == fd) {
            if (ENOENT == errno && fatal_flag) {
                fatalf("Cannot open '%s' because\n"
                       "\tthe parent directory does not exist.\n"
                       "\tPlease create the directory.\n", path);
            } else if (EACCES == errno && fatal_flag) {
                fatalf("Cannot open '%s' for writing.\n"
                       "\tThe parent directory must be writeable by the\n"
                       "\tuser '%s', which is the cache_effective_user\n"
                       "\tset in squid.conf.", path, Config.effectiveUser);
            } else if (EISDIR == errno && fatal_flag) {
                fatalf("Cannot open '%s' because it is a directory, not a file.\n", path);
            } else {
                debugs(50, 1, "logfileOpen: " << path << ": " << xstrerror());
                return NULL;
            }
        }

        lf->fd = fd;

        if (bufsz > 0) {
            lf->buf = (char *) xmalloc(bufsz);
            lf->bufsz = bufsz;
        }
    }

    if (fatal_flag)
        lf->flags.fatal = 1;

    return lf;
}