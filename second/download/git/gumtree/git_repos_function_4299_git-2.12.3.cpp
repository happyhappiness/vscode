static int canonical_name(const char *host, struct strbuf *out)
{
	int status = -1;

#ifndef NO_IPV6
	struct addrinfo hints, *ai;
	memset (&hints, '\0', sizeof (hints));
	hints.ai_flags = AI_CANONNAME;
	if (!getaddrinfo(host, NULL, &hints, &ai)) {
		if (ai && ai->ai_canonname && strchr(ai->ai_canonname, '.')) {
			strbuf_addstr(out, ai->ai_canonname);
			status = 0;
		}
		freeaddrinfo(ai);
	}
#else
	struct hostent *he = gethostbyname(host);
	if (he && strchr(he->h_name, '.')) {
		strbuf_addstr(out, he->h_name);
		status = 0;
	}
#endif /* NO_IPV6 */

	return status;
}