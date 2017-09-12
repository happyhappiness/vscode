void aofChildPipeReadable(aeEventLoop *el, int fd, void *privdata, int mask) {
    char byte;

    if (read(fd,&byte,1) == 1 && byte == '!') {
        redisLog(REDIS_NOTICE,"AOF rewrite child asks to stop sending diffs.");
        server.aof_stop_sending_diff = 1;
        write(server.aof_pipe_write_ack_to_child,"!",1);
    }
    /* Remove the handler since this can be called only one time during a
     * rewrite. */
    aeDeleteFileEvent(server.el,server.aof_pipe_read_ack_from_child,AE_READABLE);
}