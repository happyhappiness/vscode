void cleanup_disable(void)
{
	cleanup_fname = cleanup_new_fname = NULL;
	cleanup_fd_r = cleanup_fd_w = -1;
	cleanup_got_literal = 0;
}