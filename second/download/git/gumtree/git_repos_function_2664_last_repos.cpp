void transport_set_verbosity(struct transport *transport, int verbosity,
	int force_progress)
{
	if (verbosity >= 1)
		transport->verbose = verbosity <= 3 ? verbosity : 3;
	if (verbosity < 0)
		transport->verbose = -1;

	/**
	 * Rules used to determine whether to report progress (processing aborts
	 * when a rule is satisfied):
	 *
	 *   . Report progress, if force_progress is 1 (ie. --progress).
	 *   . Don't report progress, if force_progress is 0 (ie. --no-progress).
	 *   . Don't report progress, if verbosity < 0 (ie. -q/--quiet ).
	 *   . Report progress if isatty(2) is 1.
	 **/
	if (force_progress >= 0)
		transport->progress = !!force_progress;
	else
		transport->progress = verbosity >= 0 && isatty(2);
}