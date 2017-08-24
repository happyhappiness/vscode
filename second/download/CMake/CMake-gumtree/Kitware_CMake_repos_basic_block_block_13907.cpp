(cs[1] == 'P' && cs[2] >= '0' && cs[2] <= '9') {
			cp = my_atoi(cs + 2);
		} else if (strcmp(cs, "CP_ACP") == 0)
			cp = get_current_codepage();
		else if (strcmp(cs, "CP_OEMCP") == 0)
			cp = get_current_oemcp()