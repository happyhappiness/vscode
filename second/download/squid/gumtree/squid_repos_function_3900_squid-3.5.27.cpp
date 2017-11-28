bool
Adaptation::ServiceGroup::findLink(const ServiceFilter &filter, Pos &pos) const
{
    return !allServicesSame && findService(filter, pos);
}