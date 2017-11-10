static int match_funcname(struct grep_opt *opt, struct grep_source *gs, char *bol, char *eol)
{
	xdemitconf_t *xecfg = opt->priv;
	if (xecfg && !xecfg->find_func) {
		grep_source_load_driver(gs);
		if (gs->driver->funcname.pattern) {
			const struct userdiff_funcname *pe = &gs->driver->funcname;
			xdiff_set_find_func(xecfg, pe->pattern, pe->cflags);
		} else {
			xecfg = opt->priv = NULL;
		}
	}

	if (xecfg) {
		char buf[1];
		return xecfg->find_func(bol, eol - bol, buf, 1,
					xecfg->find_func_priv) >= 0;
	}

	if (bol == eol)
		return 0;
	if (isalpha(*bol) || *bol == '_' || *bol == '$')
		return 1;
	return 0;
}