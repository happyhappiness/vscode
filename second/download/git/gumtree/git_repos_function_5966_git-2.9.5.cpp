off_t buffer_skip_bytes(struct line_buffer *buf, off_t nbytes)
{
	char byte_buffer[COPY_BUFFER_LEN];
	off_t done = 0;
	while (done < nbytes && !feof(buf->infile) && !ferror(buf->infile)) {
		off_t len = nbytes - done;
		size_t in = len < COPY_BUFFER_LEN ? len : COPY_BUFFER_LEN;
		done += fread(byte_buffer, 1, in, buf->infile);
	}
	return done;
}