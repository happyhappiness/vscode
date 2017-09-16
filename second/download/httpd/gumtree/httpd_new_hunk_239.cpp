	    if (!(autoindex_opts & SUPPRESS_SIZE)) {

		ap_send_size(ar[x]->size, r);

		ap_rputs("  ", r);

	    }

	    if (!(autoindex_opts & SUPPRESS_DESC)) {

		if (ar[x]->desc) {

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

    else {

	ap_rputs("</UL>", r);

    }

}



/*

 * Compare two file entries according to the sort criteria.  The return

 * is essentially a signum function value.

 */



static int dsortf(struct ent **e1, struct ent **e2)

{

    struct ent *c1;

    struct ent *c2;

    int result = 0;



    /*

     * First, see if either of the entries is for the parent directory.

     * If so, that *always* sorts lower than anything else.

     */

    if (is_parent((*e1)->name)) {

        return -1;

    }

    if (is_parent((*e2)->name)) {

        return 1;

    }

    /*

     * All of our comparisons will be of the c1 entry against the c2 one,

     * so assign them appropriately to take care of the ordering.

     */

    if ((*e1)->ascending) {

        c1 = *e1;

        c2 = *e2;

    }

    else {

        c1 = *e2;

        c2 = *e1;

    }

    switch (c1->key) {

    case K_LAST_MOD:

	if (c1->lm > c2->lm) {

            return 1;

        }

        else if (c1->lm < c2->lm) {

            return -1;

        }

        break;

    case K_SIZE:

        if (c1->size > c2->size) {

            return 1;

        }

        else if (c1->size < c2->size) {

            return -1;

        }

        break;

    case K_DESC:

        result = strcmp(c1->desc ? c1->desc : "", c2->desc ? c2->desc : "");

        if (result) {

            return result;

        }

        break;

    }

    return strcmp(c1->name, c2->name);

}





static int index_directory(request_rec *r, autoindex_config_rec * autoindex_conf)

{

    char *title_name = ap_escape_html(r->pool, r->uri);

