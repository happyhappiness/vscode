void set_sock_opts (int sockfd) /* {{{ */
{
	int status;
	int socktype;

	socklen_t socklen = sizeof (socklen_t);
	int so_keepalive = 1;

	status = getsockopt (sockfd, SOL_SOCKET, SO_TYPE, &socktype, &socklen);
	if (status != 0)
	{
		WARNING ("set_sock_opts: failed to determine socket type");
		return;
	}

	if (socktype == SOCK_STREAM)
	{
		status = setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE,
				&so_keepalive, sizeof (so_keepalive));
		if (status != 0)
			WARNING ("set_sock_opts: failed to set socket keepalive flag");

#ifdef TCP_KEEPIDLE
		int tcp_keepidle = ((CDTIME_T_TO_MS(plugin_get_interval()) - 1) / 100 + 1);
		status = setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE,
				&tcp_keepidle, sizeof (tcp_keepidle));
		if (status != 0)
			WARNING ("set_sock_opts: failed to set socket tcp keepalive time");
#endif

#ifdef TCP_KEEPINTVL
		int tcp_keepintvl = ((CDTIME_T_TO_MS(plugin_get_interval()) - 1) / 1000 + 1);
		status = setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL,
				&tcp_keepintvl, sizeof (tcp_keepintvl));
		if (status != 0)
			WARNING ("set_sock_opts: failed to set socket tcp keepalive interval");
#endif
	}
}