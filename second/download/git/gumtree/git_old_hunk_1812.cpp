		fprintf(o->file, "%s", header.buf);
		strbuf_reset(&header);
		goto free_ab_and_return;
	} else if (!DIFF_OPT_TST(o, TEXT) &&
	    ( (!textconv_one && diff_filespec_is_binary(one)) ||
	      (!textconv_two && diff_filespec_is_binary(two)) )) {
		if (fill_mmfile(&mf1, one) < 0 || fill_mmfile(&mf2, two) < 0)
			die("unable to read files to diff");
		/* Quite common confusing case */
		if (mf1.size == mf2.size &&
		    !memcmp(mf1.ptr, mf2.ptr, mf1.size)) {
			if (must_show_header)
