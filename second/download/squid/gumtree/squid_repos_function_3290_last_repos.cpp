bool
Adaptation::ServiceGroup::wants(const ServiceFilter &filter) const
{
    Pos pos = 0;
    return findService(filter, pos);
}