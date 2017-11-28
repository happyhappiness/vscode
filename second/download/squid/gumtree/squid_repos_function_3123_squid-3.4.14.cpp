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