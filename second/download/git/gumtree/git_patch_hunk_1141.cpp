 			url_nr = states.remote->pushurl_nr;
 		} else {
 			url = states.remote->url;
 			url_nr = states.remote->url_nr;
 		}
 		for (i = 0; i < url_nr; i++)
-			/* TRANSLATORS: the colon ':' should align with
-			   the one in "  Fetch URL: %s" translation */
+			/*
+			 * TRANSLATORS: the colon ':' should align
+			 * with the one in " Fetch URL: %s"
+			 * translation.
+			 */
 			printf_ln(_("  Push  URL: %s"), url[i]);
 		if (!i)
 			printf_ln(_("  Push  URL: %s"), _("(no URL)"));
 		if (no_query)
 			printf_ln(_("  HEAD branch: %s"), _("(not queried)"));
 		else if (!states.heads.nr)
