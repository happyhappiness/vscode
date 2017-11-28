void
MimeIcon::load()
{
    const char *type = mimeGetContentType(icon);

    if (type == NULL)
        fatal("Unknown icon format while reading mime.conf\n");

    StoreEntry::getPublic(this, url, METHOD_GET);
}