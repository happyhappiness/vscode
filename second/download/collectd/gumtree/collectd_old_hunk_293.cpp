				usage (argv[0]);
		} /* switch (c) */
	}

	if ((socket_file_g == NULL) || (value_string_g == NULL)
			|| (hostname_g == NULL))
		usage (argv[0]);

	return (do_check ());
} /* int main */
