bool Adaptation::Icap::Xaction::doneAll() const
{
    return !connector && !securer && !reader && !writer && Adaptation::Initiate::doneAll();
}