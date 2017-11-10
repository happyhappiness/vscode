static int tloop_join(pthread_t thread, const char *name)
{
	int err;
	void *tret;
	err = pthread_join(thread, &tret);
	if (!tret) {
		error("%s thread failed", name);
		return 1;
	}
	if (err) {
		error("%s thread failed to join: %s", name, strerror(err));
		return 1;
	}
	return 0;
}