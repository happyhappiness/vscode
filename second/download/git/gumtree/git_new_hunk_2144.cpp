			    !strcmp(last_stage0->name, ce->name))
				ce->ce_flags |= CE_UPDATE;
		}
	}
}

static const char * const ls_files_usage[] = {
	N_("git ls-files [options] [<file>...]"),
	NULL
};

static int option_parse_z(const struct option *opt,
