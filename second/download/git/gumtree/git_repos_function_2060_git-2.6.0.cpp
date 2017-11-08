static int write_refs_to_temp_dir(struct strbuf *temp_dir,
				  int refspec_nr, const char **refspec)
{
	int i;

	for (i = 0; i < refspec_nr; i++) {
		struct object_id oid;
		char *ref;

		if (dwim_ref(refspec[i], strlen(refspec[i]), oid.hash, &ref) != 1)
			return error("Could not get ref %s", refspec[i]);

		if (write_one_ref(ref, &oid, 0, temp_dir)) {
			free(ref);
			return -1;
		}
		free(ref);
	}
	return 0;
}