static void xs_init (pTHX)
{
	char *file = __FILE__;

	dXSUB_SYS;

	/* build the Collectd module into the perl interpreter */
	Perl_newXS (perl, "Collectd::bootstrap", boot_Collectd, file);

	/* enable usage of Perl modules using shared libraries */
	Perl_newXS (perl, "DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
	return;
}