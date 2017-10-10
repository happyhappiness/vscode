		} else if (!s->show_untracked_files) {
			if (s->hints)
				printf(_("nothing to commit (use -u to show untracked files)\n"));
			else
				printf(_("nothing to commit\n"));
		} else
			printf(_("nothing to commit, working directory clean\n"));
	}
}

static void wt_shortstatus_unmerged(struct string_list_item *it,
			   struct wt_status *s)
{
