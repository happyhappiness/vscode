static int cldap_config (oconfig_item_t *ci) /* {{{ */
{
	int i;
	int status = 0;

	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("Instance", child->key) == 0)
			cldap_config_add (child);
		else
			WARNING ("openldap plugin: The configuration option "
					"\"%s\" is not allowed here. Did you "
					"forget to add an <Instance /> block "
					"around the configuration?",
					child->key);
	} /* for (ci->children) */

	return (status);
}