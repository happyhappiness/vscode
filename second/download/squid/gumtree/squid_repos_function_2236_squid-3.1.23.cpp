static void
idnsReadVC(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (flag == COMM_ERR_CLOSING)
        return;

    if (flag != COMM_OK || len <= 0) {
        comm_close(fd);
        return;
    }

    vc->msg->size += len;       // XXX should not access -> size directly

    if (vc->msg->contentSize() < vc->msglen) {
        comm_read(fd, buf + len, vc->msglen - vc->msg->contentSize(), idnsReadVC, vc);
        return;
    }

    assert(vc->ns < nns);
    debugs(78, 3, "idnsReadVC: FD " << fd << ": received " <<
           (int) vc->msg->contentSize() << " bytes via tcp from " <<
           nameservers[vc->ns].S << ".");

    idnsGrokReply(vc->msg->buf, vc->msg->contentSize());
    vc->msg->clean();
    comm_read(fd, (char *)&vc->msglen, 2 , idnsReadVCHeader, vc);
}