int strbuf_getcwd(struct strbuf *sb)
{
	size_t oldalloc = sb->alloc;
	size_t guessed_len = 128;

	for (;; guessed_len *= 2) {
		strbuf_grow(sb, guessed_len);
		if (getcwd(sb->buf, sb->alloc)) {
			strbuf_setlen(sb, strlen(sb->buf));
			return 0;
		}

		/*
		 * If getcwd(3) is implemented as a syscall that falls
		 * back to a regular lookup using readdir(3) etc. then
		 * we may be able to avoid EACCES by providing enough
		 * space to the syscall as it's not necessarily bound
		 * to the same restrictions as the fallback.
		 */
		if (errno == EACCES && guessed_len < PATH_MAX)
			continue;

		if (errno != ERANGE)
			break;
	}
	if (oldalloc == 0)
		strbuf_release(sb);
	else
		strbuf_reset(sb);
	return -1;
}