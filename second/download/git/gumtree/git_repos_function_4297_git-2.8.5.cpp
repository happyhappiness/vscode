static void setup_default_push_refspecs(struct remote *remote)
{
	struct branch *branch = branch_get(NULL);
	int triangular = is_workflow_triangular(remote);

	switch (push_default) {
	default:
	case PUSH_DEFAULT_MATCHING:
		add_refspec(":");
		break;

	case PUSH_DEFAULT_UNSPECIFIED:
	case PUSH_DEFAULT_SIMPLE:
		if (triangular)
			setup_push_current(remote, branch);
		else
			setup_push_upstream(remote, branch, triangular, 1);
		break;

	case PUSH_DEFAULT_UPSTREAM:
		setup_push_upstream(remote, branch, triangular, 0);
		break;

	case PUSH_DEFAULT_CURRENT:
		setup_push_current(remote, branch);
		break;

	case PUSH_DEFAULT_NOTHING:
		die(_("You didn't specify any refspecs to push, and "
		    "push.default is \"nothing\"."));
		break;
	}
}