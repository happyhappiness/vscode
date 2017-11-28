void Adaptation::Icap::Preview::wrote(size_t size, bool wroteEof)
{
    Must(enabled());

    theWritten += size;

    Must(theWritten <= theAd);

    if (wroteEof)
        theState = stIeof; // written size is irrelevant
    else if (theWritten >= theAd)
        theState = stDone;
}