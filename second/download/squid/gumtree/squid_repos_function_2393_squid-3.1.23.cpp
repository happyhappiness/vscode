void FwdState::start(Pointer aSelf)
{
    // Protect ourselves from being destroyed when the only Server pointing
    // to us is gone (while we expect to talk to more Servers later).
    // Once we set self, we are responsible for clearing it when we do not
    // expect to talk to any servers.
    self = aSelf; // refcounted

    // We hope that either the store entry aborts or peer is selected.
    // Otherwise we are going to leak our object.

    entry->registerAbort(FwdState::abort, this);
    peerSelect(request, entry, fwdStartCompleteWrapper, this);

    // TODO: set self _after_ the peer is selected because we do not need
    // self until we start talking to some Server.
}