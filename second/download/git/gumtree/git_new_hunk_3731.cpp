					len1, p->one->path,
					len2, p->two->path,
					len1, p->one->path,
					len2, p->two->path);
		git_SHA1_Update(&ctx, buffer, len1);

		if (diff_header_only)
			continue;

		if (fill_mmfile(&mf1, p->one) < 0 ||
		    fill_mmfile(&mf2, p->two) < 0)
			return error("unable to read files to diff");

		if (diff_filespec_is_binary(p->one) ||
		    diff_filespec_is_binary(p->two)) {
			git_SHA1_Update(&ctx, oid_to_hex(&p->one->oid),
					40);
			git_SHA1_Update(&ctx, oid_to_hex(&p->two->oid),
					40);
			continue;
		}

		xpp.flags = 0;
		xecfg.ctxlen = 3;
		xecfg.flags = 0;
