SBufList
Acl::AllOf::dump() const
{
    return empty() ? SBufList() : nodes.front()->dump();
}