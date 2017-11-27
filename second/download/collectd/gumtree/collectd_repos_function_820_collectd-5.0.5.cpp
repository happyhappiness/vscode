static int g_interval_get (pTHX_ SV *var, MAGIC *mg)
{
	cdtime_t *interval = (cdtime_t *)mg->mg_ptr;
	double nv;

	nv = CDTIME_T_TO_DOUBLE (*interval);

	sv_setnv (var, nv);
	return 0;
}