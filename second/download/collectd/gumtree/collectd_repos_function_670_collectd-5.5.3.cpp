static int ps_config (oconfig_item_t *ci)
{
	int i;

#if KERNEL_LINUX
	const size_t max_procname_len = 15;
#elif KERNEL_SOLARIS || KERNEL_FREEBSD
	const size_t max_procname_len = MAXCOMLEN -1;
#endif

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (strcasecmp (c->key, "Process") == 0)
		{
			if ((c->values_num != 1)
					|| (OCONFIG_TYPE_STRING != c->values[0].type)) {
				ERROR ("processes plugin: `Process' expects exactly "
						"one string argument (got %i).",
						c->values_num);
				continue;
			}

			if (c->children_num != 0) {
				WARNING ("processes plugin: the `Process' config option "
						"does not expect any child elements -- ignoring "
						"content (%i elements) of the <Process '%s'> block.",
						c->children_num, c->values[0].value.string);
			}

#if KERNEL_LINUX || KERNEL_SOLARIS || KERNEL_FREEBSD
			if (strlen (c->values[0].value.string) > max_procname_len) {
				WARNING ("processes plugin: this platform has a %zu character limit "
						"to process names. The `Process \"%s\"' option will "
						"not work as expected.",
						max_procname_len, c->values[0].value.string);
			}
#endif

			ps_list_register (c->values[0].value.string, NULL);
		}
		else if (strcasecmp (c->key, "ProcessMatch") == 0)
		{
			if ((c->values_num != 2)
					|| (OCONFIG_TYPE_STRING != c->values[0].type)
					|| (OCONFIG_TYPE_STRING != c->values[1].type))
			{
				ERROR ("processes plugin: `ProcessMatch' needs exactly "
						"two string arguments (got %i).",
						c->values_num);
				continue;
			}

			if (c->children_num != 0) {
				WARNING ("processes plugin: the `ProcessMatch' config option "
						"does not expect any child elements -- ignoring "
						"content (%i elements) of the <ProcessMatch '%s' '%s'> "
						"block.", c->children_num, c->values[0].value.string,
						c->values[1].value.string);
			}

			ps_list_register (c->values[0].value.string,
					c->values[1].value.string);
		}
		else
		{
			ERROR ("processes plugin: The `%s' configuration option is not "
					"understood and will be ignored.", c->key);
			continue;
		}
	}

	return (0);
}