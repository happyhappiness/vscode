static int cldap_init_host (cldap_t *st) /* {{{ */
{
	LDAP *ld;
	int rc;

	if (st->state && st->ld)
	{
		DEBUG ("openldap plugin: Already connected to %s", st->url);
		return (0);
	}

	rc = ldap_initialize (&ld, st->url);
	if (rc != LDAP_SUCCESS)
	{
		ERROR ("openldap plugin: ldap_initialize failed: %s",
			ldap_err2string (rc));
		st->state = 0;
		ldap_unbind_ext_s (ld, NULL, NULL);
		return (-1);
	}

	st->ld = ld;

	ldap_set_option (st->ld, LDAP_OPT_PROTOCOL_VERSION, &st->version);

	ldap_set_option (st->ld, LDAP_OPT_TIMEOUT,
		&(const struct timeval){st->timeout, 0});

	ldap_set_option (st->ld, LDAP_OPT_RESTART, LDAP_OPT_ON);

	if (st->cacert != NULL)
		ldap_set_option (st->ld, LDAP_OPT_X_TLS_CACERTFILE, st->cacert);

	if (st->verifyhost == 0)
	{
		int never = LDAP_OPT_X_TLS_NEVER;
		ldap_set_option (st->ld, LDAP_OPT_X_TLS_REQUIRE_CERT, &never);
	}

	if (st->starttls != 0)
	{
		rc = ldap_start_tls_s (ld, NULL, NULL);
		if (rc != LDAP_SUCCESS)
		{
			ERROR ("openldap plugin: Failed to start tls on %s: %s",
					st->url, ldap_err2string (rc));
			st->state = 0;
			ldap_unbind_ext_s (st->ld, NULL, NULL);
			return (-1);
		}
	}

	struct berval cred;
	if (st->password != NULL)
	{
		cred.bv_val = st->password;
		cred.bv_len = strlen (st->password);
	}
	else
	{
		cred.bv_val = "";
		cred.bv_len = 0;
	}

	rc = ldap_sasl_bind_s (st->ld, st->binddn, LDAP_SASL_SIMPLE, &cred,
			NULL, NULL, NULL);
	if (rc != LDAP_SUCCESS)
	{
		ERROR ("openldap plugin: Failed to bind to %s: %s",
				st->url, ldap_err2string (rc));
		st->state = 0;
		ldap_unbind_ext_s (st->ld, NULL, NULL);
		return (-1);
	}
	else
	{
		DEBUG ("openldap plugin: Successfully connected to %s",
				st->url);
		st->state = 1;
		return (0);
	}
}