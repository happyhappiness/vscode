static void mod_info_module_cmds(request_rec * r, const command_rec * cmds,
				 ap_directive_t * conftree)
{
    const command_rec *cmd;
    ap_directive_t *tmptree = conftree;
    char htmlstring[MAX_STRING_LEN];
    int block_start = 0;
    int nest = 0;

    while (tmptree != NULL) {
	cmd = cmds;
	while (cmd->name) {
	    if ((cmd->name[0] != '<') && 
                (strcasecmp(cmd->name, tmptree->directive) == 0)) {
		if (nest > block_start) {
		    block_start++;
		    apr_snprintf(htmlstring, sizeof(htmlstring), "%s %s",
                                tmptree->parent->directive,
				tmptree->parent->args);
                    ap_rputs("<dd><tt>", r);
                    mod_info_html_cmd_string(r, htmlstring, 0);
                    ap_rputs("</tt></dd>\n", r);
		}
		if (nest == 2) {
		    ap_rprintf(r, "<dd><tt>&nbsp;&nbsp;&nbsp;&nbsp;%s "
			       "<i>%s</i></tt></dd>\n",
                               ap_escape_html(r->pool,tmptree->directive), 
                               ap_escape_html(r->pool,tmptree->args));
		} else if (nest == 1) {
		    ap_rprintf(r,
			       "<dd><tt>&nbsp;&nbsp;%s <i>%s</i></tt></dd>\n",
                               ap_escape_html(r->pool,tmptree->directive), 
                               ap_escape_html(r->pool,tmptree->args));
		} else {
                    ap_rputs("<dd><tt>", r);
                    mod_info_html_cmd_string(r, tmptree->directive, 0);
                    ap_rprintf(r, " <i>%s</i></tt></dd>\n", 
                               ap_escape_html(r->pool,tmptree->args));
		}
	    }
	    ++cmd;
	}
	if (tmptree->first_child != NULL) {
	    tmptree = tmptree->first_child;
	    nest++;
	} else if (tmptree->next != NULL) {
	    tmptree = tmptree->next;
	} else {
	    if (block_start) {
		apr_snprintf(htmlstring, sizeof(htmlstring), "%s %s",
			    tmptree->parent->directive,
			    tmptree->parent->args);
		ap_rputs("<dd><tt>", r);
                mod_info_html_cmd_string(r, htmlstring, 1);
                ap_rputs("</tt></dd>\n", r);
		block_start--;
	    }
            if (tmptree->parent) {
                tmptree = tmptree->parent->next;
            }
            else {
                tmptree = NULL;
            }
	    nest--;
	}

    }
}