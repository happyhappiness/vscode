int inet_aton(const char *cp, struct in_addr *inp)
{
	unsigned int a1, a2, a3, a4;
	unsigned long ret;

	if (strcmp(cp, "255.255.255.255") == 0) {
		inp->s_addr = (unsigned) -1;
		return 0;
	}

	if (sscanf(cp, "%u.%u.%u.%u", &a1, &a2, &a3, &a4) != 4 ||
	    a1 > 255 || a2 > 255 || a3 > 255 || a4 > 255) {
		return 0;
	}

	ret = (a1 << 24) | (a2 << 16) | (a3 << 8) | a4;

	inp->s_addr = htonl(ret);
	
	if (inp->s_addr == (unsigned) -1) {
		return 0;
	}
	return 1;
}