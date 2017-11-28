static const char* epolltype_atoi(int x)
{
    switch (x) {

    case EPOLL_CTL_ADD:
        return "EPOLL_CTL_ADD";

    case EPOLL_CTL_DEL:
        return "EPOLL_CTL_DEL";

    case EPOLL_CTL_MOD:
        return "EPOLL_CTL_MOD";

    default:
        return "UNKNOWN_EPOLLCTL_OP";
    }
}