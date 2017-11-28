static char *
errorTryLoadText(const char *page_name, const char *dir, bool silent)
{
    int fd;
    char path[MAXPATHLEN];
    char buf[4096];
    char *text;
    ssize_t len;
    MemBuf textbuf;

    // maybe received compound parts, maybe an absolute page_name and no dir
    if (dir)
        snprintf(path, sizeof(path), "%s/%s", dir, page_name);
    else
        snprintf(path, sizeof(path), "%s", page_name);

    fd = file_open(path, O_RDONLY | O_TEXT);

    if (fd < 0) {
        /* with dynamic locale negotiation we may see some failures before a success. */
        if (!silent)
            debugs(4, DBG_CRITICAL, HERE << "'" << path << "': " << xstrerror());
        return NULL;
    }

    textbuf.init();

    while ((len = FD_READ_METHOD(fd, buf, sizeof(buf))) > 0) {
        textbuf.append(buf, len);
    }

    if (len < 0) {
        debugs(4, DBG_CRITICAL, HERE << "failed to fully read: '" << path << "': " << xstrerror());
    }

    file_close(fd);

    /* Shrink memory size down to exact size. MemBuf has a tencendy
     * to be rather large..
     */
    text = xstrdup(textbuf.buf);

    textbuf.clean();

    return text;
}