void
FtpStateData::completeForwarding()
{
    if (fwd == NULL || flags.completed_forwarding) {
        debugs(9, 3, HERE << "completeForwarding avoids " <<
               "double-complete on FD " << ctrl.conn->fd << ", Data FD " << data.conn->fd <<
               ", this " << this << ", fwd " << fwd);
        return;
    }

    flags.completed_forwarding = true;
    ServerStateData::completeForwarding();
}