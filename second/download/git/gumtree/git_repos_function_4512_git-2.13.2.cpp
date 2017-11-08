static void commit_pager_choice(void) {
	switch (use_pager) {
	case 0:
		setenv("GIT_PAGER", "cat", 1);
		break;
	case 1:
		setup_pager();
		break;
	default:
		break;
	}
}