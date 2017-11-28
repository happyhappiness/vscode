
        if (regcomp(&re, pattern, re_flags) != 0) {
            debugs(25, DBG_IMPORTANT, "mimeInit: regcomp error: '" << buf << "'");
            continue;
        }

        m = new MimeEntry(pattern,re,type,encoding,mode,view_option,
                          download_option,icon);

        *MimeTableTail = m;

        MimeTableTail = &m->next;

        debugs(25, 5, "mimeInit: added '" << buf << "'");
    }

    fclose(fp);

    for (m = MimeTable; m != NULL; m = m->next)
        m->theIcon.load();
    debugs(25, DBG_IMPORTANT, "Finished loading MIME types and icons.");
}

void
mimeFreeMemory(void)
{
    MimeEntry *m;

    while ((m = MimeTable)) {
        MimeTable = m->next;
        delete m;
    }

    MimeTableTail = &MimeTable;
}

void
MimeIcon::load()
{
    const char *type = mimeGetContentType(icon_);

    if (type == NULL)
        fatal("Unknown icon format while reading mime.conf\n");

    StoreEntry::getPublic(this, url_, Http::METHOD_GET);
}

void
MimeIcon::created (StoreEntry *newEntry)
{
    /* if the icon is already in the store, do nothing */
    if (!newEntry->isNull())
        return;

    int fd;
    int n;
    RequestFlags flags;
    struct stat sb;
    LOCAL_ARRAY(char, path, MAXPATHLEN);
    char *buf;

    snprintf(path, MAXPATHLEN, "%s/%s", Config.icons.directory, icon_);

    fd = file_open(path, O_RDONLY | O_BINARY);
    if (fd < 0) {
        debugs(25, DBG_CRITICAL, "Problem opening icon file " << path << ": " << xstrerror());
        return;
    }
    if (fstat(fd, &sb) < 0) {
        debugs(25, DBG_CRITICAL, "Problem opening icon file. Fd: " << fd << ", fstat error " << xstrerror());
        file_close(fd);
        return;
    }

    flags.cachable = true;
    StoreEntry *e = storeCreateEntry(url_,url_,flags,Http::METHOD_GET);
    assert(e != NULL);
    EBIT_SET(e->flags, ENTRY_SPECIAL);
    e->setPublicKey();
    e->buffer();
    HttpRequest *r = HttpRequest::CreateFromUrl(url_);

    if (NULL == r)
        fatal("mimeLoadIcon: cannot parse internal URL");

    e->mem_obj->request = r;
    HTTPMSGLOCK(e->mem_obj->request);

    HttpReply *reply = new HttpReply;

    reply->setHeaders(Http::scOkay, NULL, mimeGetContentType(icon_), sb.st_size, sb.st_mtime, -1);
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
    e->unlock();
    memFree(buf, MEM_4K_BUF);
    debugs(25, 3, "Loaded icon " << url_);
}

MimeEntry::~MimeEntry()
{
    xfree(pattern);
    xfree(content_type);
    xfree(content_encoding);
    regfree(&compiled_pattern);
}

MimeEntry::MimeEntry(const char *aPattern, const regex_t &compiledPattern,
                     const char *aContentType, const char *aContentEncoding,
                     const char *aTransferMode, bool optionViewEnable,
                     bool optionDownloadEnable, const char *anIconName) :
        pattern(xstrdup(aPattern)),
        compiled_pattern(compiledPattern),
        content_type(xstrdup(aContentType)),
        content_encoding(xstrdup(aContentEncoding)),
        view_option(optionViewEnable),
        download_option(optionViewEnable),
        theIcon(anIconName), next(NULL)
{
    if (!strcasecmp(aTransferMode, "ascii"))
        transfer_mode = 'A';
    else if (!strcasecmp(aTransferMode, "text"))
        transfer_mode = 'A';
    else
        transfer_mode = 'I';
}
