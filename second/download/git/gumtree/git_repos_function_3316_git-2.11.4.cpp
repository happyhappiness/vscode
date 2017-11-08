static void flush(struct sha1file *f, const void *buf, unsigned int count)
{
	if (0 <= f->check_fd && count)  {
		unsigned char check_buffer[8192];
		ssize_t ret = read_in_full(f->check_fd, check_buffer, count);

		if (ret < 0)
			die_errno("%s: sha1 file read error", f->name);
		if (ret < count)
			die("%s: sha1 file truncated", f->name);
		if (memcmp(buf, check_buffer, count))
			die("sha1 file '%s' validation error", f->name);
	}

	for (;;) {
		int ret = xwrite(f->fd, buf, count);
		if (ret > 0) {
			f->total += ret;
			display_throughput(f->tp, f->total);
			buf = (char *) buf + ret;
			count -= ret;
			if (count)
				continue;
			return;
		}
		if (!ret)
			die("sha1 file '%s' write error. Out of diskspace", f->name);
		die_errno("sha1 file '%s' write error", f->name);
	}
}