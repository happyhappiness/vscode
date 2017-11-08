static int match_address(char *addr, char *tok)
{
	char *p;
	unsigned long a, t, mask = (unsigned long)~0;

	if (!addr || !*addr) return 0;

	if (!isdigit(tok[0])) return 0;

	p = strchr(tok,'/');
	if (p) *p = 0;

	a = inet_addr(addr);
	t = inet_addr(tok);

	if (p) {
		*p = '/';
	}

	if (t == INADDR_NONE) {
		rprintf(FERROR,"malformed address %s\n", tok);
		return 0;
	}

	a = ntohl(a);
	t = ntohl(t);

	if (p) {
		if (strchr(p+1,'.')) {
			mask = inet_addr(p+1);
			if (mask == INADDR_NONE) {
				rprintf(FERROR,"malformed mask in %s\n", tok);
				return 0;
			}
			mask = ntohl(mask);
		} else {
			int bits = atoi(p+1);
			if (bits <= 0 || bits > 32) {
				rprintf(FERROR,"malformed mask in %s\n", tok);
				return 0;
			}
			mask &= (mask << (32-bits));
		}
	}

	return ((a&mask) == (t&mask));
}