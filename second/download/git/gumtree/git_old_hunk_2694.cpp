
		memset(&xpp, 0, sizeof(xpp));
		memset(&xecfg, 0, sizeof(xecfg));
		xpp.flags = o->xdl_opts;
		xecfg.ctxlen = o->context;
		xecfg.interhunkctxlen = o->interhunkcontext;
		xdi_diff_outf(&mf1, &mf2, diffstat_consume, diffstat,
			      &xpp, &xecfg);
	}

	diff_free_filespec_data(one);
	diff_free_filespec_data(two);
}

