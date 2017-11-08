static int match_binary(char *b1, char *b2, char *mask, int addrlen)
{
	int i;

	for (i=0; i<addrlen; i++) {
		if ((b1[i]^b2[i])&mask[i]) {
			return 0;
		}
	}

	return 1;
}