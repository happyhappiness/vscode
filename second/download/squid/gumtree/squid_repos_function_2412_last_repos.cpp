void
HttpRequest::detailError(err_type aType, int aDetail)
{
    if (errType || errDetail)
        debugs(11, 5, HERE << "old error details: " << errType << '/' << errDetail);
    debugs(11, 5, HERE << "current error details: " << aType << '/' << aDetail);
    // checking type and detail separately may cause inconsistency, but
    // may result in more details available if they only become available later
    if (!errType)
        errType = aType;
    if (!errDetail)
        errDetail = aDetail;
}