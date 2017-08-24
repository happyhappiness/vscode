(strncmp(iter->value, value, len) == 0 &&
		    (iter->value[len] == '\0' ||
		     iter->value[len] == '='))
			break;