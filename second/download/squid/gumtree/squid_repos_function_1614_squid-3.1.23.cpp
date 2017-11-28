HttpHdrScTarget *
httpHdrScFindTarget (HttpHdrSc *sc, const char *target)
{
    dlink_node *node;
    assert (sc);
    node = sc->targets.head;

    while (node) {
        HttpHdrScTarget *sct = (HttpHdrScTarget *)node->data;

        if (target && sct->target.defined() && !strcmp (target, sct->target.termedBuf()))
            return sct;
        else if (!target && sct->target.undefined())
            return sct;

        node = node->next;
    }

    return NULL;
}