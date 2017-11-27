		status = lcc_identifier_to_string (connection,
				id, sizeof (id), ret_ident + i);
		if (status != 0) {
			printf ("ERROR: listval: Failed to convert returned "
					"identifier to a string: %s\n",
					lcc_strerror (connection));
			continue;
		}

		/* skip over the (empty) hostname and following '/' */
		printf ("\t%s\n", id + 1);
	}

	if (ret_ident != NULL)
		free (ret_ident);
	return (RET_OKAY);
} /* int do_listval */

static int do_check_con_none (size_t values_num,
		double *values, char **values_names)
{
