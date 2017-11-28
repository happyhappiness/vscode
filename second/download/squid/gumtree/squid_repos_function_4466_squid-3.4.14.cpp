wordlist*
Acl::AllOf::dump() const
{
    return empty() ? NULL : nodes.front()->dump();
}