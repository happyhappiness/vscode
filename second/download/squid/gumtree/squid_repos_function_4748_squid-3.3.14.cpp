CossMemBuf *
CossSwapDir::storeCossFilenoToMembuf(sfileno f)
{
    CossMemBuf *t = NULL;
    dlink_node *m;
    off_t o = storeCossFilenoToDiskOffset(f);

    for (m = membufs.head; m; m = m->next) {
        t = (CossMemBuf *)m->data;

        if ((o >= (off_t)t->diskstart) && (o < (off_t)t->diskend))
            break;
    }

    assert(t);
    return t;
}