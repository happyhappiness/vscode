bool
mimeGetDownloadOption(const char *fn)
{
    MimeEntry *m = mimeGetEntry(fn, 1);
    return m ? m->download_option : 0;
}