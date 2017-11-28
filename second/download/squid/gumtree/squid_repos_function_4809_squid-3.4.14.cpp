void
Http::StatusLine::set(const Http::ProtocolVersion &newVersion, const Http::StatusCode newStatus, const char *newReason)
{
    protocol = AnyP::PROTO_HTTP;
    version = newVersion;
    status_ = newStatus;
    /* Note: no xstrdup for 'reason', assumes constant 'reasons' */
    reason_ = newReason;
}