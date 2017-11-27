static int perl_config_includedir (oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type))
		return 1;

	if (NULL == aTHX) {
		log_warn ("EnableDebugger has no effects if used after LoadPlugin.");
		return 1;
	}

	value = ci->values[0].value.string;

	if (NULL == perl) {
		perl_argv = (char **)realloc (perl_argv,
				(++perl_argc + 1) * sizeof (char *));

		if (NULL == perl_argv) {
			log_err ("perl_config: Not enough memory.");
			exit (3);
		}

		perl_argv[perl_argc - 1] = (char *)smalloc (strlen (value) + 3);
		sstrncpy(perl_argv[perl_argc - 1], "-I", 3);
		sstrncpy(perl_argv[perl_argc - 1] + 2, value, strlen (value) + 1);

		perl_argv[perl_argc] = NULL;
	}
	else {
		/* prepend the directory to @INC */
		Perl_av_unshift (perl, GvAVn (PL_incgv), 1);
		Perl_av_store (perl, GvAVn (PL_incgv),
				0, Perl_newSVpv (perl, value, strlen (value)));
	}
	return 0;
}