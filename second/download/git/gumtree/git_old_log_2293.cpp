die(_("unable to look up current user in the passwd file: %s"),
		    errno ? strerror(errno) : _("no such user"));