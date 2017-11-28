Adaptation::ServicePointer
Adaptation::ServicePlan::replacement(const ServiceFilter &filter)
{
    if (!atEof && !group->findReplacement(filter, ++pos))
        atEof = true;
    return current();
}