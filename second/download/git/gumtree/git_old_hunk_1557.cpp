			strbuf_setlen(gitdir, gitdir_offset);
		else
			strbuf_addch(&dir, '/');
		strbuf_insert(gitdir, gitdir_offset, dir.buf, dir.len);
	}

	strbuf_reset(&dir);
	strbuf_addf(&dir, "%s/config", gitdir->buf + gitdir_offset);
	read_repository_format(&candidate, dir.buf);
	strbuf_release(&dir);

	if (verify_repository_format(&candidate, &err) < 0) {
		warning("ignoring git dir '%s': %s",
			gitdir->buf + gitdir_offset, err.buf);
		strbuf_release(&err);
		strbuf_setlen(gitdir, gitdir_offset);
		return NULL;
	}

	return gitdir->buf + gitdir_offset;
}

const char *setup_git_directory_gently(int *nongit_ok)
{
	static struct strbuf cwd = STRBUF_INIT;
	struct strbuf dir = STRBUF_INIT, gitdir = STRBUF_INIT;
