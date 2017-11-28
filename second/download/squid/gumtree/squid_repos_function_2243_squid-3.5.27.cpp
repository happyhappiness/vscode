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

#if WRITES_MAINTAIN_DISK_OFFSET
    if (F->disk.offset != ctrl_dat->offset) {
#else
    {
#endif
        debugs(6, 3, "diskHandleRead: FD " << fd << " seeking to offset " << ctrl_dat->offset);
        lseek(fd, ctrl_dat->offset, SEEK_SET);  /* XXX ignore return? */
        ++ statCounter.syscalls.disk.seeks;
        F->disk.offset = ctrl_dat->offset;
    }

    errno = 0;
    len = FD_READ_METHOD(fd, ctrl_dat->buf, ctrl_dat->req_len);

    if (len > 0)
        F->disk.offset += len;

    ++ statCounter.syscalls.disk.reads;

    fd_bytes(fd, len, FD_READ);

    if (len < 0) {
        if (ignoreErrno(errno)) {
            Comm::SetSelect(fd, COMM_SELECT_READ, diskHandleRead, ctrl_dat, 0);
            PROF_stop(diskHandleRead);
            return;
        }

        debugs(50, DBG_IMPORTANT, "diskHandleRead: FD " << fd << ": " << xstrerror());
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

/* start read operation */
/* buffer must be allocated from the caller.
 * It must have at least req_len space in there.
 * call handler when a reading is complete. */
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

void
safeunlink(const char *s, int quiet)
{
    ++ statCounter.syscalls.disk.unlinks;

    if (unlink(s) < 0 && !quiet)
        debugs(50, DBG_IMPORTANT, "safeunlink: Couldn't delete " << s << ": " << xstrerror());
}

/*
 * Same as rename(2) but complains if something goes wrong;
 * the caller is responsible for handing and explaining the
 * consequences of errors.
 */
int
xrename(const char *from, const char *to)
{
    debugs(21, 2, "xrename: renaming " << from << " to " << to);
#if _SQUID_OS2_ || _SQUID_WINDOWS_
    remove(to);
#endif

    if (0 == rename(from, to))
        return 0;

    debugs(21, errno == ENOENT ? 2 : 1, "xrename: Cannot rename " << from << " to " << to << ": " << xstrerror());

    return -1;
}