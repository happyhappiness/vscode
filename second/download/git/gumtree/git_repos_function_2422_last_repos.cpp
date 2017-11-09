int main(int ac, char **av)
{
	char buf[1024];

	if (!strcmp(av[1], "-e")) {
		int len = strlen(av[2]);
		encode_85(buf, av[2], len);
		if (len <= 26) len = len + 'A' - 1;
		else len = len + 'a' - 26 - 1;
		printf("encoded: %c%s\n", len, buf);
		return 0;
	}
	if (!strcmp(av[1], "-d")) {
		int len = *av[2];
		if ('A' <= len && len <= 'Z') len = len - 'A' + 1;
		else len = len - 'a' + 26 + 1;
		decode_85(buf, av[2]+1, len);
		printf("decoded: %.*s\n", len, buf);
		return 0;
	}
	if (!strcmp(av[1], "-t")) {
		char t[4] = { -1,-1,-1,-1 };
		encode_85(buf, t, 4);
		printf("encoded: D%s\n", buf);
		return 0;
	}
}