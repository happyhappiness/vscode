clientStreamNode *
clientStreamNode::prev() const
{
    if (node.prev)
        return (clientStreamNode *)node.prev->data;
    else
        return NULL;
}