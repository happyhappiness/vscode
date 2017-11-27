static int g_iv_get (pTHX_ SV *var, MAGIC *mg)
{
	int *iv = (int *)mg->mg_ptr;
	sv_setiv (var, *iv);
	return 0;
}