Adaptation::ServicePointer
Adaptation::ServicePlan::current() const
{
    // may return NULL even if not atEof
    return atEof ? Adaptation::ServicePointer() : group->at(pos);
}