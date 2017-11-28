void Adaptation::Icap::Xaction::disableRetries()
{
    debugs(93,5, typeName << (isRetriable ? " from now on" : " still") <<
           " cannot be retried " << status());
    isRetriable = false;
}