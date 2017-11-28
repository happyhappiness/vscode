bool
Ipc::TypedMsgHdr::hasFd() const
{
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(this);
    return cmsg &&
           cmsg->cmsg_level == SOL_SOCKET &&
           cmsg->cmsg_type == SCM_RIGHTS;
}