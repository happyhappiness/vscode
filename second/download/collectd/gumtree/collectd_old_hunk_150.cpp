			fprintf (stderr, "Unable to load plugin %s.\n", type);
		}
	}

	closedir (dh);

	return (ret);
}

/*
 * The `register_*' functions follow
 */
