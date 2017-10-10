			continue;
		}

		xpp.flags = 0;
		xecfg.ctxlen = 3;
		xecfg.flags = 0;
		xdi_diff_outf(&mf1, &mf2, patch_id_consume, &data,
			      &xpp, &xecfg);
	}

	git_SHA1_Final(sha1, &ctx);
	return 0;
}

