{
			if (value == NULL)
				iso9660->opt.rr = OPT_RR_DISABLED;
			else if (strcmp(value, "1") == 0)
				iso9660->opt.rr = OPT_RR_USEFUL;
			else if (strcmp(value, "strict") == 0)
				iso9660->opt.rr = OPT_RR_STRICT;
			else if (strcmp(value, "useful") == 0)
				iso9660->opt.rr = OPT_RR_USEFUL;
			else
				goto invalid_value;
			return (ARCHIVE_OK);
		}