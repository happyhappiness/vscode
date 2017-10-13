static void refuse_unconfigured_deny(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(refuse_unconfigured_deny_msg); i++)
		rp_error("%s", refuse_unconfigured_deny_msg[i]);
}