		/* This means the bisection process succeeded. */
		exit(10);
	}

	nr = all - reaches - 1;
	steps = estimate_bisect_steps(all);
	xsnprintf(steps_msg, sizeof(steps_msg),
		  Q_("(roughly %d step)", "(roughly %d steps)", steps),
		  steps);
	/* TRANSLATORS: the last %s will be replaced with
	   "(roughly %d steps)" translation */
	printf(Q_("Bisecting: %d revision left to test after this %s\n",
		  "Bisecting: %d revisions left to test after this %s\n",
		  nr), nr, steps_msg);

	return bisect_checkout(bisect_rev, no_checkout);
}

static inline int log2i(int n)
{
