void freeaddrinfo(struct addrinfo *res)
{
	struct addrinfo *next = NULL;

	for (;res; res = next) {
		next = res->ai_next;
		if (res->ai_canonname) {
			free(res->ai_canonname);
		}
		if (res->ai_addr) {
			free(res->ai_addr);
		}
		free(res);
	}
}