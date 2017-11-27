static int g_iv_set (pTHX_ SV *var, MAGIC *mg)
{
	int *iv = (int *)mg->mg_ptr;
	*iv = (int)SvIV (var);
	return 0;
}