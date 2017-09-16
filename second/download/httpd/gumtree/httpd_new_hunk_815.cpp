	    p->next = head;

	    head = p;

	    num_ent++;

	}

    }

    if (num_ent > 0) {

	ar = (struct ent **) ap_palloc(r->pool,

				       num_ent * sizeof(struct ent *));

	p = head;

	x = 0;

	while (p) {

	    ar[x++] = p;

	    p = p->next;

	}



	qsort((void *) ar, num_ent, sizeof(struct ent *),

	      (int (*)(const void *, const void *)) dsortf);

    }

    output_directories(ar, num_ent, autoindex_conf, r, autoindex_opts, keyid,

		       direction);

    ap_pclosedir(r->pool, d);



    if ((tmp = find_readme(autoindex_conf, r))) {

	if (!insert_readme(name, tmp, "",

			   ((autoindex_opts & FANCY_INDEXING) ? HRULE

			                                      : NO_HRULE),

			   END_MATTER, r)) {

	    ap_rputs(ap_psignature("<HR>\n", r), r);

	}

    }

    ap_rputs("</BODY></HTML>\n", r);



    ap_kill_timeout(r);

