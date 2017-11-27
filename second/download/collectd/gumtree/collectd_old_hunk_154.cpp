		fprintf (stderr, "Cannot set the interval to a correct value.\n"
				"Please check your settings.\n");
		return (-1);
	}
	DEBUG ("interval_g = %i;", interval_g);

	return (0);
} /* int init_global_variables */

static int change_basedir (const char *orig_dir)
{
	char *dir = strdup (orig_dir);
