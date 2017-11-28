void
clientStreamNode::removeFromStream()
{
    if (head)
        dlinkDelete(&node, head);

    head = NULL;
}