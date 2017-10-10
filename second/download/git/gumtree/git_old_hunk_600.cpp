			fetch_refspec = transport->remote->fetch;
			fetch_refspec_nr = transport->remote->fetch_refspec_nr;
		}

		for (i = 0; i < fetch_refspec_nr; i++)
			get_fetch_map(ref_map, &fetch_refspec[i], &oref_tail, 1);

		if (tags == TAGS_SET)
			get_fetch_map(remote_refs, tag_refspec, &tail, 0);
	} else if (refmap_array) {
		die("--refmap option is only meaningful with command-line refspec(s).");
	} else {
		/* Use the defaults */
		struct remote *remote = transport->remote;
		struct branch *branch = branch_get(NULL);
