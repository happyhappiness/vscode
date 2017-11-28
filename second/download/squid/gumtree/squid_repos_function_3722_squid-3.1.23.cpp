Adaptation::ServicePointer
Adaptation::ServicePlan::next(const ServiceFilter &filter)
{
    if (!atEof && !group->findLink(filter, ++pos))
        atEof = true;
    return current();
}