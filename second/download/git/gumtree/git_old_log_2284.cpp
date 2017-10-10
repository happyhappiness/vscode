error(_("cannot read %s: %s"), filename, ferror(f) ?
			strerror(errno) : _("unexpected end of file"));