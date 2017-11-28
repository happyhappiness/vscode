uint64_t Adaptation::Icap::SizedEstimate::size() const
{
    Must(knownSize());
    return static_cast<uint64_t>(theData);
}