bool Adaptation::Ecap::ServiceRep::wantsUrl(const SBuf &urlPath) const
{
    Must(up());
    SBuf nonConstUrlPath = urlPath;
    // c_str() reallocates and terminates for libecap API
    return theService->wantsUrl(nonConstUrlPath.c_str());
}