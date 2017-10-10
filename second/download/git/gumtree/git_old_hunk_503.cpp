 * process entirely).
 *
 * The writing side could use stdio, but since the reading
 * side can't, we stay with pure read/write interfaces.
 */
void packet_flush(int fd);
void packet_write(int fd, const char *fmt, ...) __attribute__((format (printf, 2, 3)));
void packet_buf_flush(struct strbuf *buf);
void packet_buf_write(struct strbuf *buf, const char *fmt, ...) __attribute__((format (printf, 2, 3)));

/*
 * Read a packetized line into the buffer, which must be at least size bytes
 * long. The return value specifies the number of bytes read into the buffer.
 *
 * If src_buffer and *src_buffer are not NULL, it should point to a buffer
