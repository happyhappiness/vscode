					len1, p->one->path,
					len2, p->two->path,
					len1, p->one->path,
					len2, p->two->path);
		git_SHA1_Update(&ctx, buffer, len1);

		if (diff_filespec_is_binary(p->one) ||
		    diff_filespec_is_binary(p->two)) {
			git_SHA1_Update(&ctx, sha1_to_hex(p->one->sha1), 40);
			git_SHA1_Update(&ctx, sha1_to_hex(p->two->sha1), 40);
			continue;
		}

		xpp.flags = 0;
		xecfg.ctxlen = 3;
		xecfg.flags = 0;
