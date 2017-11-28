static void
idnsSentQueryVC(int fd, char *buf, size_t size, comm_err_t flag, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (flag == COMM_ERR_CLOSING)
        return;

    if (fd_table[fd].closing())
        return;

    if (flag != COMM_OK || size <= 0) {
        comm_close(fd);
        return;
    }

    vc->busy = 0;
    idnsDoSendQueryVC(vc);
}