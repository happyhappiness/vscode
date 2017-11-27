static int config (oconfig_item_t *ci)
{
	int status = 0;
	int i;
	oconfig_item_t *lci = NULL; /* legacy config */

	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("Instance", child->key) == 0 && child->children_num > 0)
			config_add (child);
		else
		{
			/* legacy mode - convert to <Instance ...> config */
			if (lci == NULL)
			{
				lci = malloc (sizeof(*lci));
				if (lci == NULL)
				{
					ERROR ("apache plugin: malloc failed.");
					return (-1);
				}
				memset (lci, '\0', sizeof (*lci));
			}

			lci->children_num++;
			lci->children =
				realloc (lci->children,
					 lci->children_num * sizeof (*child));
			if (lci->children == NULL)
			{
				ERROR ("apache plugin: realloc failed.");
				return (-1);
			}
			memcpy (&lci->children[lci->children_num-1], child, sizeof (*child));
		}
	} /* for (ci->children) */

	if (lci)
	{
		/* create a <Instance ""> entry */
		lci->key = "Instance";
		lci->values_num = 1;
		lci->values = (oconfig_value_t *) malloc (lci->values_num * sizeof (oconfig_value_t));
		lci->values[0].type = OCONFIG_TYPE_STRING;
		lci->values[0].value.string = "";

		status = config_add (lci);
		sfree (lci->values);
		sfree (lci->children);
		sfree (lci);
	}

	return status;
}