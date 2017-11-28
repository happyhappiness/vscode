SBufList
ACLDomainData::dump() const
{
    AclDomainDataDumpVisitor visitor;
    domains->visit(visitor);
    return visitor.contents;
}