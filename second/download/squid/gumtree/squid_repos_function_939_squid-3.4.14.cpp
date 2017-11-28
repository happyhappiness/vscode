bool
commHasHalfClosedMonitor(int fd)
{
    return TheHalfClosed->has(fd);
}