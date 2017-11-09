static int match_binary(const char *b1, const char *b2, const char *mask, int addrlen)
{
	int i;

	for (i = 0; i < addrlen; i++) {
		if ((b1[i] ^ b2[i]) & mask[i])
			return 0;
	}

	return 1;
}