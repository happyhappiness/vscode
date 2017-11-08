static void gen_challenge(char *addr, char *challenge)
{
	char input[32];
	char md4_out[MD4_SUM_LENGTH];
	struct timeval tv;

	memset(input, 0, sizeof input);

	strlcpy((char *)input, addr, 17);
	sys_gettimeofday(&tv);
	SIVAL(input, 16, tv.tv_sec);
	SIVAL(input, 20, tv.tv_usec);
	SIVAL(input, 24, getpid());

	sum_init(0);
	sum_update(input, sizeof input);
	sum_end(md4_out);

	base64_encode(md4_out, MD4_SUM_LENGTH, challenge);
}