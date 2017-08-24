{
		al = get_argument(&as, cmd);
		if (al < 0) {
			r = ARCHIVE_FAILED;/* Invalid sequence. */
			goto exit_function;
		}
		if (al == 0)
			break;
		cmd += al;
		if (archive_strlen(&as) == 0 && *cmd == '\0')
			break;
		r = cmdline_add_arg(data, as.s);
		if (r != ARCHIVE_OK)
			goto exit_function;
	}