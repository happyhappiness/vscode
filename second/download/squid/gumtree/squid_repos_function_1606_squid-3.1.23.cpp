HttpHdrSc *
httpHdrScDup(const HttpHdrSc * sc)
{
    HttpHdrSc *dup;
    dlink_node *node;
    assert(sc);
    node = sc->targets.head;
    dup = httpHdrScCreate();

    while (node) {
        HttpHdrScTarget *dupsct;
        dupsct = httpHdrScTargetDup ((HttpHdrScTarget *)node->data);
        dlinkAddTail (dupsct, &dupsct->node, &dup->targets);
        node = node->next;
    }

    return dup;
}