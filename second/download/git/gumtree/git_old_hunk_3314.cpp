			url_nr = states.remote->pushurl_nr;
		} else {
			url = states.remote->url;
			url_nr = states.remote->url_nr;
		}
		for (i = 0; i < url_nr; i++)
			printf_ln(_("  Push  URL: %s"), url[i]);
		if (!i)
			printf_ln(_("  Push  URL: %s"), "(no URL)");
		if (no_query)
			printf_ln(_("  HEAD branch: %s"), "(not queried)");
		else if (!states.heads.nr)
