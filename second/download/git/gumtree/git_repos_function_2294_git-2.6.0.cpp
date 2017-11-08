static void show_signature(struct rev_info *opt, struct commit *commit)
{
	struct strbuf payload = STRBUF_INIT;
	struct strbuf signature = STRBUF_INIT;
	struct strbuf gpg_output = STRBUF_INIT;
	int status;

	if (parse_signed_commit(commit, &payload, &signature) <= 0)
		goto out;

	status = verify_signed_buffer(payload.buf, payload.len,
				      signature.buf, signature.len,
				      &gpg_output, NULL);
	if (status && !gpg_output.len)
		strbuf_addstr(&gpg_output, "No signature\n");

	show_sig_lines(opt, status, gpg_output.buf);

 out:
	strbuf_release(&gpg_output);
	strbuf_release(&payload);
	strbuf_release(&signature);
}