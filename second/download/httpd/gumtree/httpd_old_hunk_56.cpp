    if (!method_restricted)
	return OK;

    if (!(sec->auth_authoritative))
	return DECLINED;

    ap_note_basic_auth_failure(r);
    return AUTH_REQUIRED;
}

module MODULE_VAR_EXPORT auth_module =
{
