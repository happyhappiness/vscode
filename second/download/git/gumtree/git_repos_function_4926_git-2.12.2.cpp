static void *fill(int min)
{
	if (min <= len)
		return buffer + offset;
	if (min > sizeof(buffer))
		die("cannot fill %d bytes", min);
	if (offset) {
		git_SHA1_Update(&ctx, buffer, offset);
		memmove(buffer, buffer + offset, len);
		offset = 0;
	}
	do {
		ssize_t ret = xread(0, buffer + len, sizeof(buffer) - len);
		if (ret <= 0) {
			if (!ret)
				die("early EOF");
			die_errno("read error on input");
		}
		len += ret;
	} while (len < min);
	return buffer;
}