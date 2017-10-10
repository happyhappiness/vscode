 			next = strchrnul(found, '\n');
 			sigc->signer = xmemdupz(found, next - found);
 		}
 	}
 }
 
+int check_signature(const char *payload, size_t plen, const char *signature,
+	size_t slen, struct signature_check *sigc)
+{
+	struct strbuf gpg_output = STRBUF_INIT;
+	struct strbuf gpg_status = STRBUF_INIT;
+	int status;
+
+	sigc->result = 'N';
+
+	status = verify_signed_buffer(payload, plen, signature, slen,
+				      &gpg_output, &gpg_status);
+	if (status && !gpg_output.len)
+		goto out;
+	sigc->payload = xmemdupz(payload, plen);
+	sigc->gpg_output = strbuf_detach(&gpg_output, NULL);
+	sigc->gpg_status = strbuf_detach(&gpg_status, NULL);
+	parse_gpg_output(sigc);
+
+ out:
+	strbuf_release(&gpg_status);
+	strbuf_release(&gpg_output);
+
+	return sigc->result != 'G' && sigc->result != 'U';
+}
+
+void print_signature_buffer(const struct signature_check *sigc, unsigned flags)
+{
+	const char *output = flags & GPG_VERIFY_RAW ?
+		sigc->gpg_status : sigc->gpg_output;
+
+	if (flags & GPG_VERIFY_VERBOSE && sigc->payload)
+		fputs(sigc->payload, stdout);
+
+	if (output)
+		fputs(output, stderr);
+}
+
 /*
  * Look at GPG signed content (e.g. a signed tag object), whose
  * payload is followed by a detached signature on it.  Return the
  * offset where the embedded detached signature begins, or the end of
  * the data when there is no such signature.
  */
