void
httpHdrScDestroy(HttpHdrSc * sc)
{
    assert(sc);

    if (sc->targets.head) {
        dlink_node *sct = sc->targets.head;

        while (sct) {
            HttpHdrScTarget *t = (HttpHdrScTarget *)sct->data;
            sct = sct->next;
            dlinkDelete (&t->node, &sc->targets);
            httpHdrScTargetDestroy (t);
        }
    }

    delete sc;
}