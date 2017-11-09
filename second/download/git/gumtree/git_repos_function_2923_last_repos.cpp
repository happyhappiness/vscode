void unable_to_lock_message(const char *path, int err, struct strbuf *buf)
{
	if (err == EEXIST) {
		strbuf_addf(buf, _("Unable to create '%s.lock': %s.\n\n"
		    "Another git process seems to be running in this repository, e.g.\n"
		    "an editor opened by 'git commit'. Please make sure all processes\n"
		    "are terminated then try again. If it still fails, a git process\n"
		    "may have crashed in this repository earlier:\n"
		    "remove the file manually to continue."),
			    absolute_path(path), strerror(err));
	} else
		strbuf_addf(buf, _("Unable to create '%s.lock': %s"),
			    absolute_path(path), strerror(err));
}