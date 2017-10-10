		sp = eol + 1;
	}
free_return:
	free(buf);
}

static int show_reference(const char *refname, const unsigned char *sha1,
			  int flag, void *cb_data)
{
	struct tag_filter *filter = cb_data;

	if (match_pattern(filter->patterns, refname)) {
		if (filter->with_commit) {
			struct commit *commit;

			commit = lookup_commit_reference_gently(sha1, 1);
			if (!commit)
				return 0;
			if (!contains(commit, filter->with_commit))
				return 0;
		}

		if (points_at.nr && !match_points_at(refname, sha1))
			return 0;

		if (!filter->lines) {
			if (filter->sort)
				string_list_append(&filter->tags, refname);
			else
				printf("%s\n", refname);
			return 0;
		}
		printf("%-15s ", refname);
		show_tag_lines(sha1, filter->lines);
		putchar('\n');
	}

	return 0;
}

