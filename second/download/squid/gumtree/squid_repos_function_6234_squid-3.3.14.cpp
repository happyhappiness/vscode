void
Ipc::TypedMsgHdr::putFd(int fd)
{
    Must(fd >= 0);
    Must(!hasFd());
    allocControl();

    const int fdCount = 1;

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(this);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int) * fdCount);

    int *fdStore = reinterpret_cast<int*>(CMSG_DATA(cmsg));
    memcpy(fdStore, &fd, fdCount * sizeof(int));
    msg_controllen = cmsg->cmsg_len;

    Must(hasFd());
}