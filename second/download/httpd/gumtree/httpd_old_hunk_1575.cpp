		    ap_rputs(terminate_description(d, ar[x]->desc,
						   autoindex_opts), r);
		}
	    }
	}
	else {
	    ap_rvputs(r, "<LI> ", anchor, " ", t2, NULL);
	}
	ap_rputc('\n', r);
    }
    if (autoindex_opts & FANCY_INDEXING) {
	ap_rputs("</PRE>", r);
    }
