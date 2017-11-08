static void read_rewind(struct connectdata *conn,
                        size_t thismuch)
{
  conn->read_pos -= thismuch;
  conn->bits.stream_was_rewound = TRUE;

#ifdef CURLDEBUG
  {
    char buf[512 + 1];
    size_t show;

    show = MIN(conn->buf_len - conn->read_pos, sizeof(buf)-1);
    if(conn->master_buffer) {
        memcpy(buf, conn->master_buffer + conn->read_pos, show);
        buf[show] = '\0';
    }
    else {
        buf[0] = '\0';
    }

    DEBUGF(infof(conn->data,
                 "Buffer after stream rewind (read_pos = %d): [%s]",
                 conn->read_pos, buf));
  }
#endif
}