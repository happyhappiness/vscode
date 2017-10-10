			/*
			 * Here we *have* to calculate the individual
			 * merge_bases again, otherwise "git merge HEAD^
			 * HEAD^^" would be missed.
			 */
			common_one = get_merge_bases(head_commit, j->item);
			if (oidcmp(&common_one->item->object.oid, &j->item->object.oid)) {
				up_to_date = 0;
				break;
			}
		}
		if (up_to_date) {
			finish_up_to_date(_("Already up-to-date. Yeeah!"));
			goto done;
		}
	}

	if (fast_forward == FF_ONLY)
		die(_("Not possible to fast-forward, aborting."));
