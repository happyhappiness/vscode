		select_timeout = allowed_lull;

	if (read_batch)
		allowed_lull = 0;
}

static void check_for_d_option_error(const char *msg)
{
	static char rsync263_opts[] = "BCDHIKLPRSTWabceghlnopqrtuvxz";
	char *colon;
	int saw_d = 0;

