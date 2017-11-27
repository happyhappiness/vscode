				{
					fprintf (stderr, "realloc failed: %s\n",
							strerror (errno));
					return (RET_UNKNOWN);
				}
				match_ds_g = tmp;
				match_ds_g[match_ds_num_g] = strdup (optarg);
				if (match_ds_g[match_ds_num_g] == NULL)
				{
					fprintf (stderr, "strdup failed: %s\n",
							strerror (errno));
					return (RET_UNKNOWN);
				}
				match_ds_num_g++;
				break;
			}
