int
Ipc::TypedMsgHdr::getFd() const
{
    Must(msg_control && msg_controllen);
    Must(hasFd());

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(this);
    Must(cmsg->cmsg_level == SOL_SOCKET);
    Must(cmsg->cmsg_type == SCM_RIGHTS);

    const int fdCount = 1;
    const int *fdStore = reinterpret_cast<const int*>(SQUID_CMSG_DATA(cmsg));
    int fd = -1;
    memcpy(&fd, fdStore, fdCount * sizeof(int));
    return fd;
}