static int log_ref_write(const char *refname, const unsigned char *old_sha1,
			 const unsigned char *new_sha1, const char *msg,
			 int flags, struct strbuf *err)
{
	return files_log_ref_write(refname, old_sha1, new_sha1, msg, flags,
				   err);
}