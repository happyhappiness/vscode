bool Adaptation::Iterator::doneAll() const
{
    return Adaptation::Initiate::doneAll() && thePlan.exhausted();
}