fprintf_ln(stderr,
			   _("WARNING: You called a Git command named '%s', "
			     "which does not exist.\n"
			     "Continuing under the assumption that you meant '%s'"),
			cmd, assumed);