die(_("Cannot update paths and switch to branch '%s' at the same time.\n"
			      "Did you intend to checkout '%s' which can not be resolved as commit?"),
			    opts.new_branch, argv[0]);