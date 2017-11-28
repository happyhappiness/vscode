CossMemBuf *
CossSwapDir::createMemBuf(off_t start, sfileno curfn, int *collision)
{
    CossMemBuf *newmb;
    CossMemBuf *t;
    StoreEntry *e;
    dlink_node *m, *prev;
    int numreleased = 0;

    CBDATA_INIT_TYPE_FREECB(CossMemBuf, NULL);
    newmb = cbdataAlloc(CossMemBuf);
    newmb->diskstart = start;
    debugs(79, 3, "CossSwapDir::createMemBuf: creating new membuf at " << newmb->diskstart);
    debugs(79, 3, "CossSwapDir::createMemBuf: at " << newmb);
    newmb->diskend = newmb->diskstart + COSS_MEMBUF_SZ;
    newmb->lockcount = 0;
    newmb->SD = this;
    /* XXX This should be reversed, with the new buffer last in the chain */
    dlinkAdd(newmb, &newmb->node, &membufs);

    /* Print out the list of membufs */

    debugs(79, 3, "CossSwapDir::createMemBuf: membuflist:");

    for (m = membufs.head; m; m = m->next) {
        t = (CossMemBuf *)m->data;
        t->describe(3, __LINE__);
    }

    /*
     * Kill objects from the tail to make space for a new chunk
     */
    for (m = cossindex.tail; m; m = prev) {
        off_t o;
        prev = m->prev;
        e = (StoreEntry *)m->data;
        o = storeCossFilenoToDiskOffset(e->swap_filen);

        if (curfn == e->swap_filen)
            *collision = 1;	/* Mark an object alloc collision */

        if ((o >= (off_t)newmb->diskstart) && (o < (off_t)newmb->diskend)) {
            e->release();
            ++numreleased;
        } else
            break;
    }

    if (numreleased > 0)
        debugs(79, 3, "CossSwapDir::createMemBuf: this allocation released " << numreleased << " storeEntries");

    ++ StoreFScoss::GetInstance().stats.stripes;

    return newmb;
}