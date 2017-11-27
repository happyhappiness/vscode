	printf ("%s: %i critical, %i warning, %i okay", status_str,
			num_critical, num_warning, num_okay);
	if (values_num > 0)
	{
		printf (" |");
		for (i = 0; i < values_num; i++)
			printf (" %s=%f;;;;", values_names[i], values[i]);
	}
	printf ("\n");

	return (status_code);
} /* int do_check_con_none */

