bool
mimeGetViewOption(const char *fn)
{
    MimeEntry *m = mimeGetEntry(fn, 0);
    return m != 0 ? m->view_option : false;
}