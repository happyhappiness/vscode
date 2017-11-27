static int cf_callback_plugin (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	DEBUG_CALLBACK (shortvar, var, arguments, value);

	if (flags == LC_FLAGS_SECTIONSTART)
	{
		if (nesting_depth != 0)
		{
			fprintf (stderr, ERR_NOT_NESTED);
			return (LC_CBRET_ERROR);
		}

		if (arguments == NULL)
		{
			fprintf (stderr, ERR_NEEDS_ARG, shortvar);
			return (LC_CBRET_ERROR);
		}

		if ((current_module = strdup (arguments)) == NULL)
		{
			perror ("strdup");
			return (LC_CBRET_ERROR);
		}

		nesting_depth++;

		if (cf_search (current_module) != NULL)
			return (LC_CBRET_OKAY);
		else
			return (LC_CBRET_IGNORESECTION);
	}
	else if (flags == LC_FLAGS_SECTIONEND)
	{
		if (current_module != NULL)
		{
			free (current_module);
			current_module = NULL;
		}

		nesting_depth--;

		return (LC_CBRET_OKAY);
	}
	else
	{
		fprintf (stderr, ERR_SECTION_ONLY, shortvar);
		return (LC_CBRET_ERROR);
	}
}