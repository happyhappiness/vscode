printf("%s%c" /* path */
			       "%s%c" /* attrname */
			       "%s%c" /* attrvalue */,
			       file, 0, git_attr_name(check[j].attr), 0, value, 0);