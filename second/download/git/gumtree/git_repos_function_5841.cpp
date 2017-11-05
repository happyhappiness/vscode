static void restore_term(void)
{
	if (term_fd < 0)
		return;

	tcsetattr(term_fd, TCSAFLUSH, &old_term);
	close(term_fd);
	term_fd = -1;
}