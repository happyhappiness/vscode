(strcmp(attr->name, "id") == 0)
			xattr->id = atol10(attr->value, strlen(attr->value))