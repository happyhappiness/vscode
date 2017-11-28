bool Adaptation::Icap::Xaction::doneAll() const
{
    return !connector && !reader && !writer && Adaptation::Initiate::doneAll();
}