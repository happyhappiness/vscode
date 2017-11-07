static void output_refs(struct ref *refs)
{
	struct ref *posn;
	for (posn = refs; posn; posn = posn->next) {
		if (posn->symref)
			printf("@%s %s\n", posn->symref, posn->name);
		else
			printf("%s %s\n", sha1_to_hex(posn->old_sha1), posn->name);
	}
	printf("\n");
	fflush(stdout);
}