void
file_read(int fd, char *buf, int req_len, off_t offset, DRCB * handler, void *client_data)
{
    dread_ctrl *ctrl_dat;
    PROF_start(file_read);
    assert(fd >= 0);
    ctrl_dat = (dread_ctrl *)memAllocate(MEM_DREAD_CTRL);
    ctrl_dat->fd = fd;
    ctrl_dat->offset = offset;
    ctrl_dat->req_len = req_len;
    ctrl_dat->buf = buf;
    ctrl_dat->end_of_file = 0;
    ctrl_dat->handler = handler;
    ctrl_dat->client_data = cbdataReference(client_data);
    diskHandleRead(fd, ctrl_dat);
    PROF_stop(file_read);
}