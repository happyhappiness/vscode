void generate_hash(char *in, char *challenge, char *out)
{
	char buf[16];

	sum_init();
	sum_update(in, strlen(in));
	sum_update(challenge, strlen(challenge));
	sum_end(buf);

	base64_encode(buf, 16, out);
}