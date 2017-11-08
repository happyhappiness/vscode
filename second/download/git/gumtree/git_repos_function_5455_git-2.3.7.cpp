off_t buffer_copy_bytes(struct line_buffer *buf, off_t nbytes)
{
	char byte_buffer[COPY_BUFFER_LEN];
	off_t done = 0;
	while (done < nbytes && !feof(buf->infile) && !ferror(buf->infile)) {
		off_t len = nbytes - done;
		size_t in = len < COPY_BUFFER_LEN ? len : COPY_BUFFER_LEN;
		in = fread(byte_buffer, 1, in, buf->infile);
		done += in;
		fwrite(byte_buffer, 1, in, stdout);
		if (ferror(stdout))
			return done + buffer_skip_bytes(buf, nbytes - done);
	}
	return done;
}