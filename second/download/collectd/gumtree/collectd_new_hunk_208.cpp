		char identifier[128];
		FORMAT_VL (identifier, sizeof (identifier), vl, ds);
		ERROR ("cmd putval: parse_value: "
				"Number of values incorrect: "
				"Got %i, expected %i. Identifier is `%s'.",
				i, vl->values_len, identifier);
		print_to_socket (fh, "-1 Number of values incorrect: "
				"Got %i, expected %i.\n",
			       	i, vl->values_len);
		return (-1);
	}

	plugin_dispatch_values (type, vl);
