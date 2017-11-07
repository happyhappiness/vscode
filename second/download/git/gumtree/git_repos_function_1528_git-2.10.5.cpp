static void setup_tracking(const char *new_ref, const char *orig_ref,
			   enum branch_track track, int quiet)
{
	struct tracking tracking;
	int config_flags = quiet ? 0 : BRANCH_CONFIG_VERBOSE;

	memset(&tracking, 0, sizeof(tracking));
	tracking.spec.dst = (char *)orig_ref;
	if (for_each_remote(find_tracked_branch, &tracking))
		return;

	if (!tracking.matches)
		switch (track) {
		case BRANCH_TRACK_ALWAYS:
		case BRANCH_TRACK_EXPLICIT:
		case BRANCH_TRACK_OVERRIDE:
			break;
		default:
			return;
		}

	if (tracking.matches > 1)
		die(_("Not tracking: ambiguous information for ref %s"),
		    orig_ref);

	if (install_branch_config(config_flags, new_ref, tracking.remote,
			      tracking.src ? tracking.src : orig_ref) < 0)
		exit(-1);

	free(tracking.src);
}