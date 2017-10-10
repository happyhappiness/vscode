		for (i = 0; i < skipped.nr; i++)
			fprintf(stderr, "  git branch -d %s\n",
				skipped.items[i].string);
	}
	string_list_clear(&skipped, 0);

	return result;
}

static void clear_push_info(void *util, const char *string)
{
	struct push_info *info = util;
