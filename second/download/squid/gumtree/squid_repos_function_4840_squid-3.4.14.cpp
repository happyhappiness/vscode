void
CossSwapDir::sync()
{
    CossMemBuf *t;
    dlink_node *m;
    off_t end;

    /* First, flush pending IO ops */
    io->sync();

    /* Then, flush any in-memory partial membufs */

    if (!membufs.head)
        return;

    for (m = membufs.head; m; m = m->next) {
        t = (CossMemBuf *)m->data;

        if (t->flags.writing) {
            debugs(79, DBG_IMPORTANT, "WARNING: sleeping for 5 seconds in storeCossSync()");
            sleep(5);		/* XXX EEEWWW! */
        }

        end = (t == current_membuf) ? current_offset : t->diskend;

        if (end > t->diskstart)
            theFile->write(new CossWrite(WriteRequest((char const *)&t->buffer, t->diskstart, end - t->diskstart, NULL), t));

        /* and flush */
        io->sync();
    }
}