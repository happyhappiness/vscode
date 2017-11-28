
        if (regcomp(&re, pattern, re_flags) != 0) {
            debugs(25, DBG_IMPORTANT, "mimeInit: regcomp error: '" << buf << "'");
            continue;
        }

        m = new mimeEntry;
        m->pattern = xstrdup(pattern);
        m->content_type = xstrdup(type);
        m->theIcon.setName(icon);
        m->content_encoding = xstrdup(encoding);
        m->compiled_pattern = re;

        if (!strcasecmp(mode, "ascii"))
            m->transfer_mode = 'A';
        else if (!strcasecmp(mode, "text"))
            m->transfer_mode = 'A';
        else
            m->transfer_mode = 'I';

        m->view_option = view_option;

        m->download_option = download_option;

        *MimeTableTail = m;

        MimeTableTail = &m->next;

        debugs(25, 5, "mimeInit: added '" << buf << "'");
    }

    fclose(fp);
    /*
     * Create Icon StoreEntry's
     */

    for (m = MimeTable; m != NULL; m = m->next)
        m->theIcon.load();

    debugs(25, DBG_IMPORTANT, "Loaded Icons.");
}

void
mimeFreeMemory(void)
{
    mimeEntry *m;

    while ((m = MimeTable)) {
        MimeTable = m->next;
        safe_free(m->pattern);
        safe_free(m->content_type);
        safe_free(m->icon);
        safe_free(m->content_encoding);
        regfree(&m->compiled_pattern);
        delete m;
    }

    MimeTableTail = &MimeTable;
}

void
MimeIcon::load()
{
    const char *type = mimeGetContentType(icon);

    if (type == NULL)
        fatal("Unknown icon format while reading mime.conf\n");

    StoreEntry::getPublic(this, url, METHOD_GET);
}

void
MimeIcon::created (StoreEntry *newEntry)
{
    /* is already in the store, do nothing */

    if (!newEntry->isNull())
        return;

    int fd;

    int n;

    RequestFlags flags;

    struct stat sb;

    LOCAL_ARRAY(char, path, MAXPATHLEN);

    char *buf;

    snprintf(path, MAXPATHLEN, "%s/%s", Config.icons.directory, icon);

    fd = file_open(path, O_RDONLY | O_BINARY);

    if (fd < 0) {
        debugs(25, DBG_CRITICAL, "mimeLoadIconFile: " << path << ": " << xstrerror());
        return;
    }

    if (fstat(fd, &sb) < 0) {
        debugs(25, DBG_CRITICAL, "mimeLoadIconFile: FD " << fd << ": fstat: " << xstrerror());
        file_close(fd);
        return;
    }

    flags.cachable = 1;
    StoreEntry *e = storeCreateEntry(url,
                                     url,
                                     flags,
                                     METHOD_GET);
    assert(e != NULL);
    EBIT_SET(e->flags, ENTRY_SPECIAL);
    e->setPublicKey();
    e->buffer();
    HttpRequest *r = HttpRequest::CreateFromUrl(url);

    if (NULL == r)
        fatal("mimeLoadIcon: cannot parse internal URL");

    e->mem_obj->request = HTTPMSGLOCK(r);

    HttpReply *reply = new HttpReply;

    reply->setHeaders(HTTP_OK, NULL, mimeGetContentType(icon), sb.st_size, sb.st_mtime, -1);

    reply->cache_control = new HttpHdrCc();

    reply->cache_control->maxAge(86400);

    reply->header.putCc(reply->cache_control);

    e->replaceHttpReply(reply);

    /* read the file into the buffer and append it to store */
    buf = (char *)memAllocate(MEM_4K_BUF);

    while ((n = FD_READ_METHOD(fd, buf, 4096)) > 0)
        e->append(buf, n);

    file_close(fd);

    e->flush();

    e->complete();

    e->timestampsSet();

    debugs(25, 3, "Loaded icon " << url);

    e->unlock();

    memFree(buf, MEM_4K_BUF);
}
