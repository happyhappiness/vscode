static void prepare_push_cert_sha1(struct child_process *proc)
{
	static int already_done;

	if (!push_cert.len)
		return;

	if (!already_done) {
		struct strbuf gpg_output = STRBUF_INIT;
		struct strbuf gpg_status = STRBUF_INIT;
		int bogs /* beginning_of_gpg_sig */;

		already_done = 1;
		if (write_sha1_file(push_cert.buf, push_cert.len, "blob", push_cert_sha1))
			hashclr(push_cert_sha1);

		memset(&sigcheck, '\0', sizeof(sigcheck));
		sigcheck.result = 'N';

		bogs = parse_signature(push_cert.buf, push_cert.len);
		if (verify_signed_buffer(push_cert.buf, bogs,
					 push_cert.buf + bogs, push_cert.len - bogs,
					 &gpg_output, &gpg_status) < 0) {
			; /* error running gpg */
		} else {
			sigcheck.payload = push_cert.buf;
			sigcheck.gpg_output = gpg_output.buf;
			sigcheck.gpg_status = gpg_status.buf;
			parse_gpg_output(&sigcheck);
		}

		strbuf_release(&gpg_output);
		strbuf_release(&gpg_status);
		nonce_status = check_nonce(push_cert.buf, bogs);
	}
	if (!is_null_sha1(push_cert_sha1)) {
		argv_array_pushf(&proc->env_array, "GIT_PUSH_CERT=%s",
				 sha1_to_hex(push_cert_sha1));
		argv_array_pushf(&proc->env_array, "GIT_PUSH_CERT_SIGNER=%s",
				 sigcheck.signer ? sigcheck.signer : "");
		argv_array_pushf(&proc->env_array, "GIT_PUSH_CERT_KEY=%s",
				 sigcheck.key ? sigcheck.key : "");
		argv_array_pushf(&proc->env_array, "GIT_PUSH_CERT_STATUS=%c",
				 sigcheck.result);
		if (push_cert_nonce) {
			argv_array_pushf(&proc->env_array,
					 "GIT_PUSH_CERT_NONCE=%s",
					 push_cert_nonce);
			argv_array_pushf(&proc->env_array,
					 "GIT_PUSH_CERT_NONCE_STATUS=%s",
					 nonce_status);
			if (nonce_status == NONCE_SLOP)
				argv_array_pushf(&proc->env_array,
						 "GIT_PUSH_CERT_NONCE_SLOP=%ld",
						 nonce_stamp_slop);
		}
	}
}