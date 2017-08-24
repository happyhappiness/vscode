{
			a->current_code = strdup(cur_charset);
			a->current_codepage = get_current_codepage();
			a->current_oemcp = get_current_oemcp();
		}