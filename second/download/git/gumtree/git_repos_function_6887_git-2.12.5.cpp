static int parse_reflist(const char *reflist)
{
	const char *ref;

	printf("refs='");
	for (ref = reflist; ref; ) {
		const char *next;
		while (*ref && isspace(*ref))
			ref++;
		if (!*ref)
			break;
		for (next = ref; *next && !isspace(*next); next++)
			;
		printf("\n%.*s", (int)(next - ref), ref);
		ref = next;
	}
	printf("'\n");

	printf("rref='");
	for (ref = reflist; ref; ) {
		const char *next, *colon;
		while (*ref && isspace(*ref))
			ref++;
		if (!*ref)
			break;
		for (next = ref; *next && !isspace(*next); next++)
			;
		if (*ref == '.')
			ref++;
		if (*ref == '+')
			ref++;
		colon = strchr(ref, ':');
		putchar('\n');
		printf("%.*s", (int)((colon ? colon : next) - ref), ref);
		ref = next;
	}
	printf("'\n");
	return 0;
}