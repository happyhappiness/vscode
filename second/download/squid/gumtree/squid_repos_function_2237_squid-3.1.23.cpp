static void
idnsReadVCHeader(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (flag == COMM_ERR_CLOSING)
        return;

    if (flag != COMM_OK || len <= 0) {
        comm_close(fd);
        return;
    }

    vc->read_msglen += len;

    assert(vc->read_msglen <= 2);

    if (vc->read_msglen < 2) {
        comm_read(fd, buf + len, 2 - vc->read_msglen, idnsReadVCHeader, vc);
        return;
    }

    vc->read_msglen = 0;

    vc->msglen = ntohs(vc->msglen);

    vc->msg->init(vc->msglen, vc->msglen);
    comm_read(fd, vc->msg->buf, vc->msglen, idnsReadVC, vc);
}