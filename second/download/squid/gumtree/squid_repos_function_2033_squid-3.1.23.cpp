static void
diskHandleRead(int fd, void *data)
{
    dread_ctrl *ctrl_dat = (dread_ctrl *)data;
    fde *F = &fd_table[fd];
    int len;
    int rc = DISK_OK;
    /*
     * FD < 0 indicates premature close; we just have to free
     * the state data.
     */

    if (fd < 0) {
        memFree(ctrl_dat, MEM_DREAD_CTRL);
        return;
    }

    PROF_start(diskHandleRead);

    if (F->disk.offset != ctrl_dat->offset) {
        debugs(6, 3, "diskHandleRead: FD " << fd << " seeking to offset " << ctrl_dat->offset);
        lseek(fd, ctrl_dat->offset, SEEK_SET);	/* XXX ignore return? */
        statCounter.syscalls.disk.seeks++;
        F->disk.offset = ctrl_dat->offset;
    }

    errno = 0;
    len = FD_READ_METHOD(fd, ctrl_dat->buf, ctrl_dat->req_len);

    if (len > 0)
        F->disk.offset += len;

    statCounter.syscalls.disk.reads++;

    fd_bytes(fd, len, FD_READ);

    if (len < 0) {
        if (ignoreErrno(errno)) {
            commSetSelect(fd, COMM_SELECT_READ, diskHandleRead, ctrl_dat, 0);
            PROF_stop(diskHandleRead);
            return;
        }

        debugs(50, 1, "diskHandleRead: FD " << fd << ": " << xstrerror());
        len = 0;
        rc = DISK_ERROR;
    } else if (len == 0) {
        rc = DISK_EOF;
    }

    if (cbdataReferenceValid(ctrl_dat->client_data))
        ctrl_dat->handler(fd, ctrl_dat->buf, len, rc, ctrl_dat->client_data);

    cbdataReferenceDone(ctrl_dat->client_data);

    memFree(ctrl_dat, MEM_DREAD_CTRL);

    PROF_stop(diskHandleRead);
}