bool
TemplateFile::loadFromFile(const char *path)
{
    int fd;
    char buf[4096];
    ssize_t len;

    if (loaded()) // already loaded?
        return true;

    fd = file_open(path, O_RDONLY | O_TEXT);

    if (fd < 0) {
        /* with dynamic locale negotiation we may see some failures before a success. */
        if (!silent && templateCode < TCP_RESET)
            debugs(4, DBG_CRITICAL, HERE << "'" << path << "': " << xstrerror());
        wasLoaded = false;
        return wasLoaded;
    }

    while ((len = FD_READ_METHOD(fd, buf, sizeof(buf))) > 0) {
        if (!parse(buf, len, false)) {
            debugs(4, DBG_CRITICAL, HERE << " parse error while reading template file: " << path);
            wasLoaded = false;
            return wasLoaded;
        }
    }
    parse(buf, 0, true);

    if (len < 0) {
        debugs(4, DBG_CRITICAL, HERE << "failed to fully read: '" << path << "': " << xstrerror());
    }

    file_close(fd);

    wasLoaded = true;
    return wasLoaded;
}