fprintf_ln(stderr, _("If you wish to set tracking information for this branch you can do so with:\n"
				"\n"
				"    git branch --set-upstream-to=%s/<branch> %s\n"),
				remote_name, curr_branch->name);