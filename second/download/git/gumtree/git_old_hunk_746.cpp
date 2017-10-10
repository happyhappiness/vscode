			else if (valid == TODO_PICK)
				return error(_("cannot cherry-pick during a revert."));
			else
				return error(_("cannot revert during a cherry-pick."));
	}

	return 0;
}

static int git_config_string_dup(char **dest,
				 const char *var, const char *value)
{
