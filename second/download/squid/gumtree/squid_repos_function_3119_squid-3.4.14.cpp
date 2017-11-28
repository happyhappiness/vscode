char
mimeGetTransferMode(const char *fn)
{
    MimeEntry *m = mimeGetEntry(fn, 0);
    return m ? m->transfer_mode : 'I';
}