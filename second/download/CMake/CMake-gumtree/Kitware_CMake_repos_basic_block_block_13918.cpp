(i = 0; acp_ocp_map[i].acp; i++) {
		if (strncmp(acp_ocp_map[i].locale, locale, len) == 0)
			return (acp_ocp_map[i].ocp);
	}