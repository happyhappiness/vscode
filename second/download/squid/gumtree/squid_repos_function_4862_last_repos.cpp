void
Http::StatusLine::clean()
{
    set(Http::ProtocolVersion(), Http::scInternalServerError, NULL);
}