SBufList
ACLHTTPStatus::dump() const
{
    HttpStatusAclDumpVisitor visitor;
    data->visit(visitor);
    return visitor.contents;
}