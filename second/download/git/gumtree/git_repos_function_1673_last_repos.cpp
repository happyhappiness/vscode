void diff_warn_rename_limit(const char *varname, int needed, int degraded_cc)
{
	if (degraded_cc)
		warning(_(degrade_cc_to_c_warning));
	else if (needed)
		warning(_(rename_limit_warning));
	else
		return;
	if (0 < needed && needed < 32767)
		warning(_(rename_limit_advice), varname, needed);
}