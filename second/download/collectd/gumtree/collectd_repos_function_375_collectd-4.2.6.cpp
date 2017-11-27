static void xs_init (pTHX)
{
	HV   *stash = NULL;
	char *file  = __FILE__;

	int i = 0;

	dXSUB_SYS;

	/* enable usage of Perl modules using shared libraries */
	Perl_newXS (perl, "DynaLoader::boot_DynaLoader", boot_DynaLoader, file);

	/* register API */
	for (i = 0; NULL != api[i].f; ++i)
		Perl_newXS (perl, api[i].name, api[i].f, file);

	stash = Perl_gv_stashpv (perl, "Collectd", 1);

	/* export "constants" */
	for (i = 0; '\0' != constants[i].name[0]; ++i)
		Perl_newCONSTSUB (perl, stash, constants[i].name,
				Perl_newSViv (perl, constants[i].value));
	return;
}