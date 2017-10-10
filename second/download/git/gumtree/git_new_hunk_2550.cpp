	strbuf_addf(&buf, "remote.%s.fetch", remote->name);
	for (i = 0; i < remote->fetch_refspec_nr; i++)
		if (git_config_set_multivar(buf.buf, remote->fetch_refspec[i], "^$", 0))
			return error(_("Could not append '%s' to '%s'"),
					remote->fetch_refspec[i], buf.buf);
	if (remote->origin == REMOTE_REMOTES)
		unlink_or_warn(git_path("remotes/%s", remote->name));
	else if (remote->origin == REMOTE_BRANCHES)
		unlink_or_warn(git_path("branches/%s", remote->name));
	return 0;
}

static int mv(int argc, const char **argv)
{
	struct option options[] = {
