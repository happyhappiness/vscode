{
			if (value == NULL)
				iso9660->opt.joliet = OPT_JOLIET_DISABLE;
			else if (strcmp(value, "1") == 0)
				iso9660->opt.joliet = OPT_JOLIET_ENABLE;
			else if (strcmp(value, "long") == 0)
				iso9660->opt.joliet = OPT_JOLIET_LONGNAME;
			else
				goto invalid_value;
			return (ARCHIVE_OK);
		}