void Adaptation::Icap::Xaction::disableRepeats(const char *reason)
{
    debugs(93,5, typeName << (isRepeatable ? " from now on" : " still") <<
           " cannot be repeated because " << reason << status());
    isRepeatable = false;
}