bool Adaptation::Icap::ModXact::gotEncapsulated(const char *section) const
{
    return icapReply->header.getByNameListMember("Encapsulated",
            section, ',').size() > 0;
}