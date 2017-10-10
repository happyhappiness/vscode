	strbuf_addstr(&path, "/info");
	safe_create_dir(path.buf, 1);

	strbuf_release(&path);
}

static void separate_git_dir(const char *git_dir, const char *git_link)
{
	struct stat st;

	if (!stat(git_link, &st)) {
		const char *src;

