SBufList
Acl::NotNode::dump() const
{
    SBufList text;
    text.push_back(SBuf(name));
    return text;
}