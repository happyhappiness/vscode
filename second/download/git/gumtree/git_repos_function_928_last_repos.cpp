int check_commit_signature(const struct commit *commit, struct signature_check *sigc)
{
	struct strbuf payload = STRBUF_INIT;
	struct strbuf signature = STRBUF_INIT;
	int ret = 1;

	sigc->result = 'N';

	if (parse_signed_commit(commit, &payload, &signature) <= 0)
		goto out;
	ret = check_signature(payload.buf, payload.len, signature.buf,
		signature.len, sigc);

 out:
	strbuf_release(&payload);
	strbuf_release(&signature);

	return ret;
}