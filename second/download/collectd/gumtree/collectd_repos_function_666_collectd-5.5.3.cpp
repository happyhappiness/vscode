static void ps_list_register (const char *name, const char *regexp)
{
	procstat_t *new;
	procstat_t *ptr;
	int status;

	new = (procstat_t *) malloc (sizeof (procstat_t));
	if (new == NULL)
	{
		ERROR ("processes plugin: ps_list_register: malloc failed.");
		return;
	}
	memset (new, 0, sizeof (procstat_t));
	sstrncpy (new->name, name, sizeof (new->name));

#if HAVE_REGEX_H
	if (regexp != NULL)
	{
		DEBUG ("ProcessMatch: adding \"%s\" as criteria to process %s.", regexp, name);
		new->re = (regex_t *) malloc (sizeof (regex_t));
		if (new->re == NULL)
		{
			ERROR ("processes plugin: ps_list_register: malloc failed.");
			sfree (new);
			return;
		}

		status = regcomp (new->re, regexp, REG_EXTENDED | REG_NOSUB);
		if (status != 0)
		{
			DEBUG ("ProcessMatch: compiling the regular expression \"%s\" failed.", regexp);
			sfree(new->re);
			sfree(new);
			return;
		}
	}
#else
	if (regexp != NULL)
	{
		ERROR ("processes plugin: ps_list_register: "
				"Regular expression \"%s\" found in config "
				"file, but support for regular expressions "
				"has been disabled at compile time.",
				regexp);
		sfree (new);
		return;
	}
#endif

	for (ptr = list_head_g; ptr != NULL; ptr = ptr->next)
	{
		if (strcmp (ptr->name, name) == 0)
		{
			WARNING ("processes plugin: You have configured more "
					"than one `Process' or "
					"`ProcessMatch' with the same name. "
					"All but the first setting will be "
					"ignored.");
#if HAVE_REGEX_H
			sfree (new->re);
#endif
			sfree (new);
			return;
		}

		if (ptr->next == NULL)
			break;
	}

	if (ptr == NULL)
		list_head_g = new;
	else
		ptr->next = new;
}