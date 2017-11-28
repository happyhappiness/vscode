int
RFCNB_Set_Sock_NoDelay(struct RFCNB_Con *con_Handle, BOOL yn)
{

    return (setsockopt(con_Handle->fd, IPPROTO_TCP, TCP_NODELAY,
                       (char *) &yn, sizeof(yn)));

}