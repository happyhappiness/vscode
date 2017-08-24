(val == NULL || strcmp(val, "off") == 0 ||
				strcmp(val, "ignore") == 0 ||
				strcmp(val, "disable") == 0 ||
				strcmp(val, "0") == 0)
			iso9660->opt_support_joliet = 0;
		else
			iso9660->opt_support_joliet = 1