SBufList
Acl::InnerNode::dump() const
{
    SBufList rv;
    for (Nodes::const_iterator i = nodes.begin(); i != nodes.end(); ++i)
        rv.push_back(SBuf((*i)->name));
    return rv;
}