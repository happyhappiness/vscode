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

#if STRICT_ORIGINAL_DST
    // Bug 3243: CVE 2009-0801
    // Bypass of browser same-origin access control in intercepted communication
    // To resolve this we must force DIRECT and only to the original client destination.
    const bool isIntercepted = request && !request->flags.redirected && (request->flags.intercepted || request->flags.interceptTproxy);
    const bool useOriginalDst = Config.onoff.client_dst_passthru || (request && !request->flags.hostVerified);
    if (isIntercepted && useOriginalDst) {
        selectPeerForIntercepted();
        // 3.2 does not suppro re-wrapping inside CONNECT.
        // our only alternative is to fake destination "found" and continue with the forwarding.
        startConnectionOrFail();
        return;
    }
#endif

    // do full route options selection
    peerSelect(&serverDestinations, request, entry, fwdPeerSelectionCompleteWrapper, this);
}