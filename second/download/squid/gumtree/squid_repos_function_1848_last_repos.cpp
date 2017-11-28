void
FwdState::syncHierNote(const Comm::ConnectionPointer &server, const char *host)
{
    if (request)
        request->hier.note(server, host);
    if (al)
        al->hier.note(server, host);
}