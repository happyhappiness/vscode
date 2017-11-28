void Adaptation::Icap::SizedEstimate::expect(int64_t aSize)
{
    theData = (aSize >= 0) ? aSize : (int64_t)dtUnknown;
}