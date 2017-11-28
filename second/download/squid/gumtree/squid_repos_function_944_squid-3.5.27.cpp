unsigned int
CommQuotaQueue::enqueue(int fd)
{
    debugs(77,5, HERE << "clt" << (const char*)clientInfo->hash.key <<
           ": FD " << fd << " with qqid" << (ins+1) << ' ' << fds.size());
    fds.push_back(fd);
    return ++ins;
}