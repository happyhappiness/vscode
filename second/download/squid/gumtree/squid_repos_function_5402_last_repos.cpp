void
Ftp::Gateway::completeForwarding()
{
    if (fwd == NULL || flags.completed_forwarding) {
        debugs(9, 3, "avoid double-complete on FD " <<
               (ctrl.conn ? ctrl.conn->fd : -1) << ", Data FD " << data.conn->fd <<
               ", this " << this << ", fwd " << fwd);
        return;
    }

    flags.completed_forwarding = true;
    Client::completeForwarding();
}