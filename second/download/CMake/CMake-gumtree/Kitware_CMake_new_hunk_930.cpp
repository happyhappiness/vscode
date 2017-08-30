	return (archive_read_support_filter_program_signature(a, cmd, NULL, 0));

}



/*

 * The bidder object stores the command and the signature to watch for.

 * The 'inhibit' entry here is used to ensure that unchecked filters never

 * bid twice in the same pipeline.

 */

struct program_bidder {

	char *description;

	char *cmd;

	void *signature;

	size_t signature_len;

