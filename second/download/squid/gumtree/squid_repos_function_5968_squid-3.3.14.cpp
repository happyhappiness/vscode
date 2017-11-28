void
esiTry::provideData (ESISegment::Pointer data, ESIElement* source)
{
    if (source == attempt) {
        flags.attemptok = 1;
        parent->provideData (data, this);
    } else if (source == except) {
        flags.exceptok = 1;
        assert (exceptbuffer == NULL);
        ESISegment::ListTransfer (data, exceptbuffer);
        notifyParent();
    }
}