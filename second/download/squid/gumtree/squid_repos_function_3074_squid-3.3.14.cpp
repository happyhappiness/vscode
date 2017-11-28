char
mimeGetTransferMode(const char *fn)
{
    mimeEntry *m = mimeGetEntry(fn, 0);
    return m ? m->transfer_mode : 'I';
}