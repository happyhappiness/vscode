int
mimeGetDownloadOption(const char *fn)
{
    mimeEntry *m = mimeGetEntry(fn, 1);
    return m ? m->download_option : 0;
}