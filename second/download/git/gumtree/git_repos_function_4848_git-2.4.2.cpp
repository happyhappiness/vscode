static int run_gpg_verify(const char *buf, unsigned long size, int verbose)
{
	int len;

	len = parse_signature(buf, size);
	if (verbose)
		write_in_full(1, buf, len);

	if (size == len)
		return error("no signature found");

	return verify_signed_buffer(buf, len, buf + len, size - len, NULL, NULL);
}