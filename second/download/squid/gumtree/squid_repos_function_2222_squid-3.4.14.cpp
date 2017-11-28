void
FwdState::serverClosed(int fd)
{
    debugs(17, 2, HERE << "FD " << fd << " " << entry->url());
    retryOrBail();
}