static void set_keep_alive(int sockfd)
{
	int ka = 1;

	if (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &ka, sizeof(ka)) < 0)
		logerror("unable to set SO_KEEPALIVE on socket: %s",
			strerror(errno));
}