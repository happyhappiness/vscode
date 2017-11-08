static int opt_command_mode_error(const struct option *opt,
				  const struct option *all_opts,
				  int flags)
{
	const struct option *that;
	struct strbuf message = STRBUF_INIT;
	struct strbuf that_name = STRBUF_INIT;

	/*
	 * Find the other option that was used to set the variable
	 * already, and report that this is not compatible with it.
	 */
	for (that = all_opts; that->type != OPTION_END; that++) {
		if (that == opt ||
		    that->type != OPTION_CMDMODE ||
		    that->value != opt->value ||
		    that->defval != *(int *)opt->value)
			continue;

		if (that->long_name)
			strbuf_addf(&that_name, "--%s", that->long_name);
		else
			strbuf_addf(&that_name, "-%c", that->short_name);
		strbuf_addf(&message, ": incompatible with %s", that_name.buf);
		strbuf_release(&that_name);
		opterror(opt, message.buf, flags);
		strbuf_release(&message);
		return -1;
	}
	return opterror(opt, ": incompatible with something else", flags);
}