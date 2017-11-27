		}
	}

	return (0);
}

int rrd_create_file (char *filename, char **ds_def, int ds_num)
{
	char **argv;
	int argc;
	int i, j;
	int status = 0;

	if (check_create_dir (filename))
		return (-1);

	argc = ds_num + rra_num + 4;

	if ((argv = (char **) malloc (sizeof (char *) * (argc + 1))) == NULL)
	{
		syslog (LOG_ERR, "rrd_create failed: %s", strerror (errno));
		return (-1);
	}

	argv[0] = "create";
	argv[1] = filename;
	argv[2] = "-s";
	argv[3] = "10";

	j = 4;
	for (i = 0; i < ds_num; i++)
		argv[j++] = ds_def[i];
	for (i = 0; i < rra_num; i++)
		argv[j++] = rra_def[i];
