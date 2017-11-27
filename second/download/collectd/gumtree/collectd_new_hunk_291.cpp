				if (strcasecmp (optarg, "none") == 0)
					consolitation_g = CON_NONE;
				else if (strcasecmp (optarg, "average") == 0)
					consolitation_g = CON_AVERAGE;
				else if (strcasecmp (optarg, "sum") == 0)
					consolitation_g = CON_SUM;
				else if (strcasecmp (optarg, "percentage") == 0)
					consolitation_g = CON_PERCENTAGE;
				else
				{
					fprintf (stderr, "Unknown consolidation function `%s'.\n",
							optarg);
					usage (argv[0]);
				}
				break;
			case 'd':
			{
				char **tmp;
				tmp = (char **) realloc (match_ds_g,
						(match_ds_num_g + 1)
