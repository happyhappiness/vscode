error(_("new mode (%o) of %s does not "
					       "match old mode (%o) of %s"),
					patch->new_mode, new_name,
					patch->old_mode, old_name);