void gitmodules_config_sha1(const unsigned char *commit_sha1)
{
	struct strbuf rev = STRBUF_INIT;
	unsigned char sha1[20];

	if (gitmodule_sha1_from_commit(commit_sha1, sha1, &rev)) {
		git_config_from_blob_sha1(git_modules_config, rev.buf,
					  sha1, NULL);
	}
	strbuf_release(&rev);
}