		/* This means the bisection process succeeded. */
		exit(10);
	}

	nr = all - reaches - 1;
	steps = estimate_bisect_steps(all);
	printf("Bisecting: %d revision%s left to test after this "
	       "(roughly %d step%s)\n", nr, (nr == 1 ? "" : "s"),
	       steps, (steps == 1 ? "" : "s"));

	return bisect_checkout(bisect_rev, no_checkout);
}

static inline int log2i(int n)
{
