(i = 1; i < n; i++)
	{
		if (strcmp(strings[i], pivot) < 0)
		{
			lesser_count++;
			tmp = (char **)realloc(lesser,
				lesser_count * sizeof(char *));
			if (!tmp) {
				free(greater);
				free(lesser);
				return (ARCHIVE_FATAL);
			}
			lesser = tmp;
			lesser[lesser_count - 1] = strings[i];
		}
		else
		{
			greater_count++;
			tmp = (char **)realloc(greater,
				greater_count * sizeof(char *));
			if (!tmp) {
				free(greater);
				free(lesser);
				return (ARCHIVE_FATAL);
			}
			greater = tmp;
			greater[greater_count - 1] = strings[i];
		}
	}