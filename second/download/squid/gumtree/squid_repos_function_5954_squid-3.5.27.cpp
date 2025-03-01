void AsyncJob::callException(const std::exception &e)
{
    // we must be called asynchronously and hence, the caller must lock us
    Must(cbdataReferenceValid(toCbdata()));

    mustStop("exception");
}