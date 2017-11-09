static int set_reuse_addr(int sockfd)
{
	int on = 1;

	if (!reuseaddr)
		return 0;
	return setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
			  &on, sizeof(on));
}