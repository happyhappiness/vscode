void
ESIContext::setError()
{
    errorpage = ERR_ESI;
    errorstatus = Http::scInternalServerError;
    flags.error = 1;
}