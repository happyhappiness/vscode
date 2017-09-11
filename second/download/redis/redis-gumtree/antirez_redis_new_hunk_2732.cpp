    return;

socket_wr_err:
    addReplySds(c,sdsnew("-IOERR error or timeout writing to target instance\r\n"));
    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;

socket_rd_err:
    addReplySds(c,sdsnew("-IOERR error or timeout reading from target node\r\n"));
    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;
