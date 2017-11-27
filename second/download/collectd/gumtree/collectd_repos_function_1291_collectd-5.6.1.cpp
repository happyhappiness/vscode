static void cldap_free (cldap_t *st) /* {{{ */
{
	if (st == NULL)
		return;

	sfree (st->binddn);
	sfree (st->password);
	sfree (st->cacert);
	sfree (st->host);
	sfree (st->name);
	sfree (st->url);
	if (st->ld)
		ldap_memfree (st->ld);
	sfree (st);
}