int lookup_name(int fd, const struct sockaddr_storage *ss,
		socklen_t ss_len,
		char *name_buf, size_t name_buf_size,
		char *port_buf, size_t port_buf_size)
{
	int name_err;

	/* reverse lookup */
	name_err = getnameinfo((struct sockaddr *) ss, ss_len,
			       name_buf, name_buf_size,
			       port_buf, port_buf_size,
			       NI_NAMEREQD | NI_NUMERICSERV);
	if (name_err != 0) {
		strlcpy(name_buf, default_name, name_buf_size);
		rprintf(FLOG, "name lookup failed for %s: %s\n",
			client_addr(fd), gai_strerror(name_err));
		return name_err;
	}

	return 0;
}