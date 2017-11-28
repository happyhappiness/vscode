void
Http::StatusLine::init()
{
    set(Http::ProtocolVersion(), Http::scNone, NULL);
}