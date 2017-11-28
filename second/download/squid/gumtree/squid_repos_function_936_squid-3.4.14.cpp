void
commStartHalfClosedMonitor(int fd)
{
    debugs(5, 5, HERE << "adding FD " << fd << " to " << *TheHalfClosed);
    assert(isOpen(fd) && !commHasHalfClosedMonitor(fd));
    (void)TheHalfClosed->add(fd); // could also assert the result
    commPlanHalfClosedCheck(); // may schedule check if we added the first FD
}