fprintf(opt->file, ":%06o %06o %s ", p->one->mode, p->two->mode,
			diff_unique_abbrev(p->one->oid.hash, opt->abbrev));