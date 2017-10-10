
static const char *ai_name(const struct addrinfo *ai)
{
	static char addr[NI_MAXHOST];
	if (getnameinfo(ai->ai_addr, ai->ai_addrlen, addr, sizeof(addr), NULL, 0,
			NI_NUMERICHOST) != 0)
		strcpy(addr, "(unknown)");

	return addr;
}

/*
 * Returns a connected socket() fd, or else die()s.
