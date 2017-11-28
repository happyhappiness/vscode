bool Adaptation::Icap::Xaction::doneWithIo() const
{
    return haveConnection() &&
           !connector && !reader && !writer && // fast checks, some redundant
           doneReading() && doneWriting();
}