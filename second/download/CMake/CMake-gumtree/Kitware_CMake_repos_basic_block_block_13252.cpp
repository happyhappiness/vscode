(attr = list->first; attr != NULL;
			    attr = attr->next) {
				if (strcmp(attr->name, "enctype") == 0 &&
				    strcmp(attr->value, "base64") == 0)
					xar->base64text = 1;
			}