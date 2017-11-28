void
FwdState::handleUnregisteredServerEnd()
{
    debugs(17, 2, HERE << "self=" << self << " err=" << err << ' ' << entry->url());
    assert(!Comm::IsConnOpen(serverConn));
    retryOrBail();
}