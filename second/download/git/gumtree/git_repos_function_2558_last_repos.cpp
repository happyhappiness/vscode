static int match_funcname(xdemitconf_t *xecfg, const char *bol, const char *eol)
{
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