char *
CossSwapDir::storeCossMemPointerFromDiskOffset(off_t offset, CossMemBuf ** mb)
{
    CossMemBuf *t;
    dlink_node *m;

    for (m = membufs.head; m; m = m->next) {
        t = (CossMemBuf *)m->data;

        if ((offset >= t->diskstart) && (offset < t->diskend)) {
            if (mb)
                *mb = t;

            return &t->buffer[offset - t->diskstart];
        }
    }

    if (mb)
        *mb = NULL;

    return NULL;
}