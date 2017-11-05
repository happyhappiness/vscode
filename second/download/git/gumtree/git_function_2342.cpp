static int sockopt_callback(void *client, curl_socket_t fd, curlsocktype type)
{
	int ka = 1;
	int rc;
	socklen_t len = (socklen_t)sizeof(ka);

	if (type != CURLSOCKTYPE_IPCXN)
		return 0;

	rc = setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&ka, len);
	if (rc < 0)
		warning("unable to set SO_KEEPALIVE on socket %s",
			strerror(errno));

	return 0; /* CURL_SOCKOPT_OK only exists since curl 7.21.5 */
}