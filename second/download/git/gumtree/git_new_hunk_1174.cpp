	if (verify) {
		/*
		 * nr_refspec must be greater than zero and i must be valid
		 * since it is only possible to reach this point from within
		 * the for loop above.
		 */
		free_refspec(i+1, rs);
		return NULL;
	}
	die("Invalid refspec '%s'", refspec[i]);
}

int valid_fetch_refspec(const char *fetch_refspec_str)
{
	struct refspec *refspec;

	refspec = parse_refspec_internal(1, &fetch_refspec_str, 1, 1);
	free_refspec(1, refspec);
	return !!refspec;
}

struct refspec *parse_fetch_refspec(int nr_refspec, const char **refspec)
{
	return parse_refspec_internal(nr_refspec, refspec, 1, 0);
