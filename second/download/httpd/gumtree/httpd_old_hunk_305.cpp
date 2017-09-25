                    mod_info_html_cmd_string(r, htmlstring, 0);
                    ap_rputs("</tt></dd>\n", r);
		}
		if (nest == 2) {
		    ap_rprintf(r, "<dd><tt>&nbsp;&nbsp;&nbsp;&nbsp;%s "
			       "<i>%s</i></tt></dd>\n",
			       tmptree->directive, tmptree->args);
		} else if (nest == 1) {
		    ap_rprintf(r,
			       "<dd><tt>&nbsp;&nbsp;%s <i>%s</i></tt></dd>\n",
			       tmptree->directive, tmptree->args);
		} else {
                    ap_rputs("<dd><tt>", r);
                    mod_info_html_cmd_string(r, tmptree->directive, 0);
                    ap_rprintf(r, " <i>%s</i></tt></dd>\n", tmptree->args);
		}
	    }
	    ++cmd;
	}
	if (tmptree->first_child != NULL) {
	    tmptree = tmptree->first_child;
