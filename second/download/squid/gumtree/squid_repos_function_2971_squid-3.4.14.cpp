void
HttpRequest::ignoreRange(const char *reason)
{
    if (range) {
        debugs(73, 3, static_cast<void*>(range) << " for " << reason);
        delete range;
        range = NULL;
    }
    // Some callers also reset isRanged but it may not be safe for all callers:
    // isRanged is used to determine whether a weak ETag comparison is allowed,
    // and that check should not ignore the Range header if it was present.
    // TODO: Some callers also delete HDR_RANGE, HDR_REQUEST_RANGE. Should we?
}