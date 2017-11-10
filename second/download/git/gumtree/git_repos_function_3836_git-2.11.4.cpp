static int verify_hostname(X509 *cert, const char *hostname)
{
	int len;
	X509_NAME *subj;
	char cname[1000];
	int i, found;
	STACK_OF(GENERAL_NAME) *subj_alt_names;

	/* try the DNS subjectAltNames */
	found = 0;
	if ((subj_alt_names = X509_get_ext_d2i(cert, NID_subject_alt_name, NULL, NULL))) {
		int num_subj_alt_names = sk_GENERAL_NAME_num(subj_alt_names);
		for (i = 0; !found && i < num_subj_alt_names; i++) {
			GENERAL_NAME *subj_alt_name = sk_GENERAL_NAME_value(subj_alt_names, i);
			if (subj_alt_name->type == GEN_DNS &&
			    strlen((const char *)subj_alt_name->d.ia5->data) == (size_t)subj_alt_name->d.ia5->length &&
			    host_matches(hostname, (const char *)(subj_alt_name->d.ia5->data)))
				found = 1;
		}
		sk_GENERAL_NAME_pop_free(subj_alt_names, GENERAL_NAME_free);
	}
	if (found)
		return 0;

	/* try the common name */
	if (!(subj = X509_get_subject_name(cert)))
		return error("cannot get certificate subject");
	if ((len = X509_NAME_get_text_by_NID(subj, NID_commonName, cname, sizeof(cname))) < 0)
		return error("cannot get certificate common name");
	if (strlen(cname) == (size_t)len && host_matches(hostname, cname))
		return 0;
	return error("certificate owner '%s' does not match hostname '%s'",
		     cname, hostname);
}