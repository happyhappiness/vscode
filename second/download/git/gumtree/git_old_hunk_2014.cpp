		} else if (has_epoch_timestamp(second)) {
			patch->is_new = 0;
			patch->is_delete = 1;
			patch->old_name = name;
		} else {
			patch->old_name = name;
			patch->new_name = null_strdup(name);
		}
	}
	if (!name)
		die(_("unable to find filename in patch at line %d"), linenr);
}

