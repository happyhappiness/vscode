static int g_pv_set (pTHX_ SV *var, MAGIC *mg)
{
	char *pv = mg->mg_ptr;
	strncpy (pv, SvPV_nolen (var), DATA_MAX_NAME_LEN);
	pv[DATA_MAX_NAME_LEN - 1] = '\0';
	return 0;
}