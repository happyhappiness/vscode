(iter = *global; iter != NULL; last = iter, iter = iter->next) {
		if (strncmp(iter->value, value, len) == 0 &&
		    (iter->value[len] == '\0' ||
		     iter->value[len] == '='))
			break;
	}