SBufList
ACLIP::dump() const
{
    IpAclDumpVisitor visitor;
    data->visit(visitor);
    return visitor.contents;
}