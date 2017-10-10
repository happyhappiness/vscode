		opt.diffopt.output_format = DIFF_FORMAT_RAW;

	log_tree_commit(&opt, commit);
}

/*
 * We use the convention that exiting with an exit code 10 means that
 * the bisection process finished successfully.
 * In this case the calling shell script should exit 0.
 *
 * If no_checkout is non-zero, the bisection process does not
 * checkout the trial commit but instead simply updates BISECT_HEAD.
