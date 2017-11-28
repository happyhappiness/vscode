Adaptation::ServicePointer Adaptation::ServiceGroup::at(const Pos pos) const
{
    return FindService(services[pos]);
}