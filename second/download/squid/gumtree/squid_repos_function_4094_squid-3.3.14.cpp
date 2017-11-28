void Adaptation::Icap::Preview::enable(size_t anAd)
{
    // TODO: check for anAd not exceeding preview size limit
    Must(!enabled());
    theAd = anAd;
    theState = stWriting;
}