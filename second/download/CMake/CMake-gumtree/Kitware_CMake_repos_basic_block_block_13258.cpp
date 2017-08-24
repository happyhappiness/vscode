(attr = list->first; attr != NULL;
			    attr = attr->next) {
				if (strcmp(attr->name, "link") != 0)
					continue;
				if (strcmp(attr->value, "original") == 0) {
					xar->file->hdnext = xar->hdlink_orgs;
					xar->hdlink_orgs = xar->file;
				} else {
					xar->file->link = (unsigned)atol10(attr->value,
					    strlen(attr->value));
					if (xar->file->link > 0)
						if (add_link(a, xar, xar->file) != ARCHIVE_OK) {
							return (ARCHIVE_FATAL);
						};
				}
			}