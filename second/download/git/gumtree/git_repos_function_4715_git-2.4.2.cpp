static char *prepare_push_cert_nonce(const char *path, unsigned long stamp)
{
	struct strbuf buf = STRBUF_INIT;
	unsigned char sha1[20];

	strbuf_addf(&buf, "%s:%lu", path, stamp);
	hmac_sha1(sha1, buf.buf, buf.len, cert_nonce_seed, strlen(cert_nonce_seed));;
	strbuf_release(&buf);

	/* RFC 2104 5. HMAC-SHA1-80 */
	strbuf_addf(&buf, "%lu-%.*s", stamp, 20, sha1_to_hex(sha1));
	return strbuf_detach(&buf, NULL);
}