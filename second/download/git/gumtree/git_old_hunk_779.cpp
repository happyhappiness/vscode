		c1 = *p1++;
		c2 = *p2++;
		state += (c1 == '0') + (isdigit (c1) != 0);
	}

	if (!initialized) {
		initialized = 1;
		prereleases = git_config_get_value_multi("versionsort.prereleasesuffix");
	}
	if (prereleases && swap_prereleases(p1 - 1, p2 - 1, &diff))
		return diff;

	state = result_type[state * 3 + (((c2 == '0') + (isdigit (c2) != 0)))];

	switch (state) {
	case CMP:
