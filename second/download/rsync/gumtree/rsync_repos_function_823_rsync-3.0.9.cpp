static int check_hostent_err(struct hostent *hp)
{
#ifndef INET6
	extern int h_errno;
#endif
	if (!hp) {
		switch (h_errno) {
			case HOST_NOT_FOUND:
			case NO_DATA:
				return EAI_NONAME;
			case TRY_AGAIN:
				return EAI_AGAIN;
			case NO_RECOVERY:
			default:
				return EAI_FAIL;
		}
	}
	if (!hp->h_name || hp->h_addrtype != AF_INET) {
		return EAI_FAIL;
	}
	return 0;
}