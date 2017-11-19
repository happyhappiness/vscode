static int parse_binary(char *buffer, unsigned long size, struct patch *patch)
{
	/*
	 * We have read "GIT binary patch\n"; what follows is a line
	 * that says the patch method (currently, either "literal" or
	 * "delta") and the length of data before deflating; a
	 * sequence of 'length-byte' followed by base-85 encoded data
	 * follows.
	 *
	 * When a binary patch is reversible, there is another binary
	 * hunk in the same format, starting with patch method (either
	 * "literal" or "delta") with the length of data, and a sequence
	 * of length-byte + base-85 encoded data, terminated with another
	 * empty line.  This data, when applied to the postimage, produces
	 * the preimage.
	 */
	struct fragment *forward;
	struct fragment *reverse;
	int status;
	int used, used_1;

	forward = parse_binary_hunk(&buffer, &size, &status, &used);
	if (!forward && !status)
		/* there has to be one hunk (forward hunk) */
		return error(_("unrecognized binary patch at line %d"), linenr-1);
	if (status)
		/* otherwise we already gave an error message */
		return status;

	reverse = parse_binary_hunk(&buffer, &size, &status, &used_1);
	if (reverse)
		used += used_1;
	else if (status) {
		/*
		 * Not having reverse hunk is not an error, but having
		 * a corrupt reverse hunk is.
		 */
		free((void*) forward->patch);
		free(forward);
		return status;
	}
	forward->next = reverse;
	patch->fragments = forward;
	patch->is_binary = 1;
	return used;
}