bool Adaptation::Icap::SizedEstimate::knownSize() const
{
    Must(expected());
    return theData != dtUnknown;
}