static void generate_hash(char *in, char *challenge, char *out)
{
	char buf[MD4_SUM_LENGTH];

	sum_init(0);
	sum_update(in, strlen(in));
	sum_update(challenge, strlen(challenge));
	sum_end(buf);

	base64_encode(buf, MD4_SUM_LENGTH, out, 0);
}