fprintf(opt->file, ":%06o %06o %s ", p->one->mode, p->two->mode,
			diff_aligned_abbrev(&p->one->oid, opt->abbrev));