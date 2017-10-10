			     "which does not exist.\n"
			     "Continuing under the assumption that you meant '%s'"),
			cmd, assumed);
		if (autocorrect > 0) {
			fprintf_ln(stderr, _("in %0.1f seconds automatically..."),
				(float)autocorrect/10.0);
			sleep_millisec(autocorrect * 100);
		}
		return assumed;
	}

	fprintf_ln(stderr, _("git: '%s' is not a git command. See 'git --help'."), cmd);

