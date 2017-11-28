void
HttpRequest::clearError()
{
    debugs(11, 7, HERE << "old error details: " << errType << '/' << errDetail);
    errType = ERR_NONE;
    errDetail = ERR_DETAIL_NONE;
}