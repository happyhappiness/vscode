static void
sum_write(struct archive_string *str, struct reg_info *reg)
{

	if (reg->compute_sum & F_CKSUM) {
		archive_string_sprintf(str, " cksum=%ju",
		    (uintmax_t)reg->crc);
	}
#ifdef ARCHIVE_HAS_MD5
	if (reg->compute_sum & F_MD5) {
		archive_strcat(str, " md5digest=");
		strappend_bin(str, reg->buf_md5, sizeof(reg->buf_md5));
	}
#endif
#ifdef ARCHIVE_HAS_RMD160
	if (reg->compute_sum & F_RMD160) {
		archive_strcat(str, " rmd160digest=");
		strappend_bin(str, reg->buf_rmd160, sizeof(reg->buf_rmd160));
	}
#endif
#ifdef ARCHIVE_HAS_SHA1
	if (reg->compute_sum & F_SHA1) {
		archive_strcat(str, " sha1digest=");
		strappend_bin(str, reg->buf_sha1, sizeof(reg->buf_sha1));
	}
#endif
#ifdef ARCHIVE_HAS_SHA256
	if (reg->compute_sum & F_SHA256) {
		archive_strcat(str, " sha256digest=");
		strappend_bin(str, reg->buf_sha256, sizeof(reg->buf_sha256));
	}
#endif
#ifdef ARCHIVE_HAS_SHA384
	if (reg->compute_sum & F_SHA384) {
		archive_strcat(str, " sha384digest=");
		strappend_bin(str, reg->buf_sha384, sizeof(reg->buf_sha384));
	}
#endif
#ifdef ARCHIVE_HAS_SHA512
	if (reg->compute_sum & F_SHA512) {
		archive_strcat(str, " sha512digest=");
		strappend_bin(str, reg->buf_sha512, sizeof(reg->buf_sha512));
	}
#endif
}