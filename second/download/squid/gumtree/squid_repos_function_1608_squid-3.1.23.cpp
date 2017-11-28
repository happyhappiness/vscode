void
httpHdrScPackInto(const HttpHdrSc * sc, Packer * p)
{
    dlink_node *node;
    assert(sc && p);
    node = sc->targets.head;

    while (node) {
        httpHdrScTargetPackInto((HttpHdrScTarget *)node->data, p);
        node = node->next;
    }
}