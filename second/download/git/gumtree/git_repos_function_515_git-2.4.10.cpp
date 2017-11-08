void parse_gpg_output(struct signature_check *sigc)
{
	const char *buf = sigc->gpg_status;
	int i;

	/* Iterate over all search strings */
	for (i = 0; i < ARRAY_SIZE(sigcheck_gpg_status); i++) {
		const char *found, *next;

		if (!skip_prefix(buf, sigcheck_gpg_status[i].check + 1, &found)) {
			found = strstr(buf, sigcheck_gpg_status[i].check);
			if (!found)
				continue;
			found += strlen(sigcheck_gpg_status[i].check);
		}
		sigc->result = sigcheck_gpg_status[i].result;
		/* The trust messages are not followed by key/signer information */
		if (sigc->result != 'U') {
			sigc->key = xmemdupz(found, 16);
			found += 17;
			next = strchrnul(found, '\n');
			sigc->signer = xmemdupz(found, next - found);
		}
	}
}