static int perl_config_includedir (pTHX_ oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("IncludeDir expects a single string argument.");
		return 1;
	}

	value = ci->values[0].value.string;

	if (NULL == aTHX) {
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
		av_unshift (GvAVn (PL_incgv), 1);
		av_store (GvAVn (PL_incgv), 0, newSVpv (value, strlen (value)));
	}
	return 0;
}