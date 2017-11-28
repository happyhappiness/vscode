bool
Adaptation::ServiceGroup::findReplacement(const ServiceFilter &filter, Pos &pos) const
{
    return allServicesSame && findService(filter, pos);
}