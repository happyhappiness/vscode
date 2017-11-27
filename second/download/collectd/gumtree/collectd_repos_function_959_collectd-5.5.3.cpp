static int g_pv_set (pTHX_ SV *var, MAGIC *mg)
{
	char *pv = mg->mg_ptr;
	sstrncpy (pv, SvPV_nolen (var), DATA_MAX_NAME_LEN);
	return 0;
}