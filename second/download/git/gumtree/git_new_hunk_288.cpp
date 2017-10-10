			if (ce->ce_flags & CE_WT_REMOVE)
				die("BUG: both update and delete flags are set on %s",
				    ce->name);
			display_progress(progress, ++cnt);
			ce->ce_flags &= ~CE_UPDATE;
			if (o->update && !o->dry_run) {
				errs |= checkout_entry(ce, state, NULL);
			}
		}
	}
	stop_progress(&progress);
	if (o->update)
		git_attr_set_direction(GIT_ATTR_CHECKIN, NULL);
