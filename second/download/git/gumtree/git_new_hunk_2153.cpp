free_return:
	free(signing_key);
	strbuf_release(&cert);
	return update_seen;
}

#define NONCE_LEN_LIMIT 256

static void reject_invalid_nonce(const char *nonce, int len)
{
	int i = 0;

	if (NONCE_LEN_LIMIT <= len)
		die("the receiving end asked to sign an invalid nonce <%.*s>",
		    len, nonce);

	for (i = 0; i < len; i++) {
		int ch = nonce[i] & 0xFF;
		if (isalnum(ch) ||
		    ch == '-' || ch == '.' ||
		    ch == '/' || ch == '+' ||
		    ch == '=' || ch == '_')
			continue;
		die("the receiving end asked to sign an invalid nonce <%.*s>",
		    len, nonce);
	}
}

int send_pack(struct send_pack_args *args,
	      int fd[], struct child_process *conn,
	      struct ref *remote_refs,
	      struct sha1_array *extra_have)
{
	int in = fd[0];
