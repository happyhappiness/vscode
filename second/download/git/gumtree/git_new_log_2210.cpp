error(_("cannot read %s: %s"), git_path_head_file(),
		      ferror(f) ?  strerror(errno) : _("unexpected end of file"));