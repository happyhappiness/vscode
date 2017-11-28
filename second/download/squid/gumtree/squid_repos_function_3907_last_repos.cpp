bool
Ssl::ErrorDetailsManager::getErrorDetail(Security::ErrorCode value, const HttpRequest::Pointer &request, ErrorDetailEntry &entry)
{
#if USE_ERR_LOCALES
    String hdr;
    if (request != NULL && request->header.getList(Http::HdrType::ACCEPT_LANGUAGE, &hdr)) {
        ErrorDetailsList::Pointer errDetails = NULL;
        //Try to retrieve from cache
        size_t pos = 0;
        char lang[256];
        // Get the first ellement of the Accept-Language header
        strHdrAcptLangGetItem(hdr, lang, 256, pos);
        errDetails = getCachedDetails(lang); // search in cache

        if (!errDetails) { // Else try to load from disk
            debugs(83, 8, HERE << "Creating new ErrDetailList to read from disk");
            errDetails = new ErrorDetailsList();
            ErrorDetailFile detailTmpl(errDetails);
            if (detailTmpl.loadFor(request.getRaw())) {
                if (detailTmpl.language()) {
                    debugs(83, 8, HERE << "Found details on disk for language " << detailTmpl.language());
                    errDetails->errLanguage = detailTmpl.language();
                    cacheDetails(errDetails);
                }
            }
        }

        if (errDetails != NULL && errDetails->getRecord(value, entry))
            return true;
    }
#endif

    // else try the default
    if (theDefaultErrorDetails->getRecord(value, entry)) {
        debugs(83, 8, HERE << "Found default details record for error: " << GetErrorName(value));
        return true;
    }

    return false;
}