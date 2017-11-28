void
HttpHdrSc::packInto(Packer * p) const
{
    dlink_node *node;
    assert(p);
    node = targets.head;

    while (node) {
        static_cast<HttpHdrScTarget *>(node->data)->packInto(p);
        node = node->next;
    }
}