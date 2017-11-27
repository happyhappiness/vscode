int perl_config (const char *key, const char *value)
{
	assert (NULL != perl);

	log_debug ("perl_config: key = \"%s\", value=\"%s\"", key, value);

	if (0 == strcasecmp (key, "LoadPlugin")) {
		char module_name[DATA_MAX_NAME_LEN];

		if (get_module_name (module_name, sizeof (module_name), value)
				== NULL) {
			log_err ("Invalid module name %s", value);
			return (1);
		} /* if (get_module_name == NULL) */

		log_debug ("perl_config: loading perl plugin \"%s\"", value);
		Perl_load_module (perl, PERL_LOADMOD_NOIMPORT,
				Perl_newSVpv (perl, module_name, strlen (module_name)),
				Nullsv);
	}
	else if (0 == strcasecmp (key, "BaseName")) {
		log_debug ("perl_config: Setting plugin basename to \"%s\"", value);
		strncpy (base_name, value, sizeof (base_name));
		base_name[sizeof (base_name) - 1] = '\0';
	}
	else if (0 == strcasecmp (key, "IncludeDir")) {
		Perl_av_unshift (perl, GvAVn (PL_incgv), 1);
		Perl_av_store (perl, GvAVn (PL_incgv),
				0, Perl_newSVpv (perl, value, strlen (value)));
	}
	else {
		return -1;
	}
	return 0;
}