mem_node const *
mem_hdr::start() const
{
    const SplayNode<mem_node *> * result = nodes.start();

    if (result)
        return result->data;

    return NULL;
}