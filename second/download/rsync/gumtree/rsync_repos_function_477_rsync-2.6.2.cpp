static int get_ai(struct addrinfo ** to_ai,
		   struct addrinfo const * pai,
		   struct afd *afd,
		   const char *addr,
		   short port)
{
	char *p;
	if ((*to_ai = (struct addrinfo *)malloc(sizeof(struct addrinfo) +
					      ((afd)->a_socklen)))
	    == NULL) 
		return 0;
	memcpy(*to_ai, pai, sizeof(struct addrinfo));
	(*to_ai)->ai_addr = (struct sockaddr *)((*to_ai) + 1);
	memset((*to_ai)->ai_addr, 0, (afd)->a_socklen);
	(*to_ai)->ai_addrlen = (afd)->a_socklen;
#if HAVE_SOCKADDR_LEN
	(*to_ai)->ai_addr->sa_len = (afd)->a_socklen;
#endif
	(*to_ai)->ai_addr->sa_family = (*to_ai)->ai_family = (afd)->a_af;
	((struct sockinet *)(*to_ai)->ai_addr)->si_port = port;
	p = (char *)((*to_ai)->ai_addr);
	memcpy(p + (afd)->a_off, (addr), (afd)->a_addrlen);
	return 1;
}