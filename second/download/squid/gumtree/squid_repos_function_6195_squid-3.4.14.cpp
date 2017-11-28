bool
esiSequence::mayFail () const
{
    if (failed)
        return true;

    return mayFail_;
}