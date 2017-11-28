void
Snmp::Forwarder::cleanup()
{
    if (fd >= 0) {
        if (closer != NULL) {
            comm_remove_close_handler(fd, closer);
            closer = NULL;
        }
        fd = -1;
    }
}