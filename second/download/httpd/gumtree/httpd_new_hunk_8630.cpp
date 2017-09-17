            else {
                p = r->main->pool;
                notes = r->main->notes;
            }

            /* Generate the response text. */
            /*
	     * Since the text is expanded by repeated calls of
             * t = pstrcat(p, t, ".."), we can avoid a little waste
             * of memory by adding the header AFTER building the list.
             * XXX: FIXME: find a way to build a string concatenation
             *             without repeatedly requesting new memory
             * XXX: FIXME: Limit the list to a maximum number of entries
             */
            t = "";

            for (i = 0; i < candidates->nelts; ++i) {

                /* The format isn't very neat... */
                t = ap_pstrcat(p, t, "<li><a href=\"", url,
			       variant[i].name, r->path_info,
			       r->parsed_uri.query ? "?" : "",
			       r->parsed_uri.query ? r->parsed_uri.query : "",
			       "\">", variant[i].name, r->path_info,
			       r->parsed_uri.query ? "?" : "",
			       r->parsed_uri.query ? r->parsed_uri.query : "",
			       "</a> (",
			       sp_reason_str[(int) (variant[i].quality)],
			       ")\n", NULL);

                /*
                 * when we have printed the "close matches" and there are
                 * more "distant matches" (matched by stripping the suffix),
                 * then we insert an additional separator text to suggest
                 * that the user LOOK CLOSELY whether these are really the
                 * files she wanted.
                 */
                if (i > 0 && i < candidates->nelts - 1
                    && variant[i].quality != SP_VERYDIFFERENT
                    && variant[i + 1].quality == SP_VERYDIFFERENT) {
                    t = ap_pstrcat(p, t, 
				   "</ul>\nFurthermore, the following related "
				   "documents were found:\n<ul>\n", NULL);
                }
            }
            t = ap_pstrcat(p, "The document name you requested (<code>",
			   r->uri,
			   "</code>) could not be found on this server.\n"
			   "However, we found documents with names similar "
			   "to the one you requested.<p>"
			   "Available documents:\n<ul>\n", t, "</ul>\n", NULL);

            /* If we know there was a referring page, add a note: */
            if (ref != NULL) {
                t = ap_pstrcat(p, t,
			       "Please consider informing the owner of the "
			       "<a href=\"", ref, 
			       "\">referring page</a> "
			       "about the broken link.\n",
			       NULL);
	    }

            /* Pass our table to http_protocol.c (see mod_negotiation): */
            ap_table_setn(notes, "variant-list", t);

            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_INFO, r,
			 ref ? "Spelling fix: %s: %d candidates from %s"
			     : "Spelling fix: %s: %d candidates",
			 r->uri, candidates->nelts, ref);

            return HTTP_MULTIPLE_CHOICES;
        }
    }

    return OK;
}

module MODULE_VAR_EXPORT speling_module =
{
    STANDARD_MODULE_STUFF,
    NULL,                       /* initializer */
    create_mconfig_for_directory,  /* create per-dir config */
    NULL,                       /* merge per-dir config */
    create_mconfig_for_server,  /* server config */
    NULL,                       /* merge server config */
    speling_cmds,               /* command table */
    NULL,                       /* handlers */
    NULL,                       /* filename translation */
    NULL,                       /* check_user_id */
    NULL,                       /* check auth */
