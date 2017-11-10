int format_tracking_info(struct branch *branch, struct strbuf *sb)
{
	int ours, theirs;
	char *base;
	int upstream_is_gone = 0;

	switch (stat_tracking_info(branch, &ours, &theirs)) {
	case 0:
		/* no base */
		return 0;
	case -1:
		/* with "gone" base */
		upstream_is_gone = 1;
		break;
	default:
		/* with base */
		break;
	}

	base = shorten_unambiguous_ref(branch->merge[0]->dst, 0);
	if (upstream_is_gone) {
		strbuf_addf(sb,
			_("Your branch is based on '%s', but the upstream is gone.\n"),
			base);
		if (advice_status_hints)
			strbuf_addf(sb,
				_("  (use \"git branch --unset-upstream\" to fixup)\n"));
	} else if (!ours && !theirs) {
		strbuf_addf(sb,
			_("Your branch is up-to-date with '%s'.\n"),
			base);
	} else if (!theirs) {
		strbuf_addf(sb,
			Q_("Your branch is ahead of '%s' by %d commit.\n",
			   "Your branch is ahead of '%s' by %d commits.\n",
			   ours),
			base, ours);
		if (advice_status_hints)
			strbuf_addf(sb,
				_("  (use \"git push\" to publish your local commits)\n"));
	} else if (!ours) {
		strbuf_addf(sb,
			Q_("Your branch is behind '%s' by %d commit, "
			       "and can be fast-forwarded.\n",
			   "Your branch is behind '%s' by %d commits, "
			       "and can be fast-forwarded.\n",
			   theirs),
			base, theirs);
		if (advice_status_hints)
			strbuf_addf(sb,
				_("  (use \"git pull\" to update your local branch)\n"));
	} else {
		strbuf_addf(sb,
			Q_("Your branch and '%s' have diverged,\n"
			       "and have %d and %d different commit each, "
			       "respectively.\n",
			   "Your branch and '%s' have diverged,\n"
			       "and have %d and %d different commits each, "
			       "respectively.\n",
			   theirs),
			base, ours, theirs);
		if (advice_status_hints)
			strbuf_addf(sb,
				_("  (use \"git pull\" to merge the remote branch into yours)\n"));
	}
	free(base);
	return 1;
}