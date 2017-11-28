clientStreamNode *
clientStreamNode::next() const
{
    if (node.next)
        return (clientStreamNode *)node.next->data;
    else
        return NULL;
}