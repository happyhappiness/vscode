static int g_interval_set (pTHX_ SV *var, MAGIC *mg)
{
	cdtime_t *interval = (cdtime_t *)mg->mg_ptr;
	double nv;

	nv = (double)SvNV (var);

	*interval = DOUBLE_TO_CDTIME_T (nv);
	return 0;
}