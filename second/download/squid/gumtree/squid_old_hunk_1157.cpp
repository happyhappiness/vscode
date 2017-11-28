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
