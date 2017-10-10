		}
		for (i = 0; i < url_nr; i++)
			/* TRANSLATORS: the colon ':' should align with
			   the one in "  Fetch URL: %s" translation */
			printf_ln(_("  Push  URL: %s"), url[i]);
		if (!i)
			printf_ln(_("  Push  URL: %s"), "(no URL)");
		if (no_query)
			printf_ln(_("  HEAD branch: %s"), "(not queried)");
		else if (!states.heads.nr)
			printf_ln(_("  HEAD branch: %s"), "(unknown)");
		else if (states.heads.nr == 1)
			printf_ln(_("  HEAD branch: %s"), states.heads.items[0].string);
		else {
			printf(_("  HEAD branch (remote HEAD is ambiguous,"
				 " may be one of the following):\n"));
			for (i = 0; i < states.heads.nr; i++)
