		status_str = "OKAY";
		status_code = RET_OKAY;
	}

	printf ("%s: %g sum |", status_str, total);
	for (i = 0; i < values_num; i++)
		printf (" %s=%g;;;;", values_names[i], values[i]);
	printf ("\n");

	return (status_code);
} /* int do_check_con_sum */

static int do_check_con_percentage (size_t values_num,
