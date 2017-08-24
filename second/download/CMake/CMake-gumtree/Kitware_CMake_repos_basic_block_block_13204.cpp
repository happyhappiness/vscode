(strcmp(attr->name, "id") == 0)
			file->id = atol10(attr->value, strlen(attr->value))