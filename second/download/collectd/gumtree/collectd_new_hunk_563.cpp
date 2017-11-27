					usage (argv[0]);
				}
				break;
			case 'd':
			{
				char **tmp;
				tmp = realloc (match_ds_g,
						(match_ds_num_g + 1)
						* sizeof (char *));
				if (tmp == NULL)
				{
					fprintf (stderr, "realloc failed: %s\n",
							strerror (errno));
