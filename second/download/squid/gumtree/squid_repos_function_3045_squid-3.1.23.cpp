int
mimeGetViewOption(const char *fn)
{
    mimeEntry *m = mimeGetEntry(fn, 0);
    return m ? m->view_option : 0;
}