free_return:
	free(signing_key);
	strbuf_release(&cert);
	return update_seen;
}

#define NONCE_LEN_LIMIT 256

static void reject_invalid_nonce(const char *nonce, int len)
{
	int i = 0;

