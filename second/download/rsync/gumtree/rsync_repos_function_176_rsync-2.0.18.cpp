static void gen_challenge(char *addr, char *challenge)
{
	char input[32];
	struct timeval tv;

	memset(input, 0, sizeof(input));

	strlcpy((char *)input, addr, 16);
	gettimeofday(&tv, NULL);
	SIVAL(input, 16, tv.tv_sec);
	SIVAL(input, 20, tv.tv_usec);
	SIVAL(input, 24, getpid());

	sum_init();
	sum_update(input, sizeof(input));
	sum_end(challenge);
}