static void handle_deletes(void)
{
	int i;
	for (i = 0; i < refspecs_nr; i++) {
		struct refspec *refspec = &refspecs[i];
		if (*refspec->src)
			continue;

		printf("reset %s\nfrom %s\n\n",
				refspec->dst, sha1_to_hex(null_sha1));
	}
}