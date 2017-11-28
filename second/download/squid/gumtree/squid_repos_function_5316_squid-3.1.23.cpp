void
ESIContext::setError()
{
    errorpage = ERR_ESI;
    errorstatus = HTTP_INTERNAL_SERVER_ERROR;
    flags.error = 1;
}