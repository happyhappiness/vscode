	} else if (!DIFF_OPT_TST(o, TEXT) &&
	    ( (!textconv_one && diff_filespec_is_binary(one)) ||
	      (!textconv_two && diff_filespec_is_binary(two)) )) {
		if (!one->data && !two->data &&
		    S_ISREG(one->mode) && S_ISREG(two->mode) &&
		    !DIFF_OPT_TST(o, BINARY)) {
			if (!oidcmp(&one->oid, &two->oid)) {
				if (must_show_header)
					fprintf(o->file, "%s", header.buf);
				goto free_ab_and_return;
			}
			fprintf(o->file, "%s", header.buf);
			fprintf(o->file, "%sBinary files %s and %s differ\n",
