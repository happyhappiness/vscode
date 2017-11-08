static int write_refs_to_temp_dir(struct strbuf *temp_dir,
		int refspec_nr, const char **refspec)
{
	int i;

	for (i = 0; i < refspec_nr; i++) {
		unsigned char sha1[20];
		char *ref;

		if (dwim_ref(refspec[i], strlen(refspec[i]), sha1, &ref) != 1)
			return error("Could not get ref %s", refspec[i]);

		if (write_one_ref(ref, sha1, 0, temp_dir)) {
			free(ref);
			return -1;
		}
		free(ref);
	}
	return 0;
}