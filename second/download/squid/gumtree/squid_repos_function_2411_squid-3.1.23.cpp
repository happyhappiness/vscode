void
FwdState::handleUnregisteredServerEnd()
{
    debugs(17, 2, "handleUnregisteredServerEnd: self=" << self <<
           " err=" << err << ' ' << entry->url());
    assert(server_fd < 0);
    retryOrBail();
}