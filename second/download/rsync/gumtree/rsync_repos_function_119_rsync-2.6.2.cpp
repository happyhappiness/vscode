int lookup_name(int fd, const struct sockaddr_storage *ss,
		socklen_t ss_len,
		char *name_buf, size_t name_buf_len,
		char *port_buf, size_t port_buf_len)
{
	int name_err;

	/* reverse lookup */
	name_err = getnameinfo((struct sockaddr *) ss, ss_len,
			       name_buf, name_buf_len,
			       port_buf, port_buf_len,
			       NI_NAMEREQD | NI_NUMERICSERV);
	if (name_err != 0) {
		strcpy(name_buf, default_name);
		rprintf(FERROR, RSYNC_NAME ": name lookup failed for %s: %s\n",
			client_addr(fd),
			gai_strerror(name_err));
		return name_err;
	}

	return 0;
}