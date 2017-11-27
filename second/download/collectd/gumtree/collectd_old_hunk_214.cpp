		fprintf (stderr, "malloc failed: %s\n",
				strerror (errno));
		free (values);
		return (-1);
	}

	{
		char *ptr = strchr (buffer, ' ') + 1;
		char *key;
		char *value;

		i = 0;
		while ((key = strtok (ptr, " \t")) != NULL)
		{
			ptr = NULL;
			value = strchr (key, '=');
			if (value == NULL)
				continue;
			*value = '\0'; value++;

			if (ignore_ds (key) != 0)
				continue;

			values_names[i] = strdup (key);
			values[i] = atof (value);

			i++;
			if (i >= values_num)
				break;
		}
		values_num = i;
	}

	*ret_values_num = values_num;
	*ret_values = values;
	*ret_values_names = values_names;

	return (0);
