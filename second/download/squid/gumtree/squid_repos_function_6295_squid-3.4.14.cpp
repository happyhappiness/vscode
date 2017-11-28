void
Ipc::Forwarder::handleRemoteAck()
{
    debugs(54, 3, HERE);
    request->requestId = 0;
    // Do not clear ENTRY_FWD_HDR_WAIT or do entry->complete() because
    // it will trigger our client side processing. Let job cleanup close.
}