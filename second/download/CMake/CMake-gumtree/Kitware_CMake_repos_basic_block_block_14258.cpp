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