{
		struct hdlink **hdlink;

		for (hdlink = &(xar->hdlink_list); *hdlink != NULL;
		    hdlink = &((*hdlink)->next)) {
			if ((*hdlink)->id == file->id) {
				struct hdlink *hltmp;
				struct xar_file *f2;
				int nlink = (*hdlink)->cnt + 1;

				file->nlink = nlink;
				for (f2 = (*hdlink)->files; f2 != NULL;
				    f2 = f2->hdnext) {
					f2->nlink = nlink;
					archive_string_copy(
					    &(f2->hardlink), &(file->pathname));
				}
				/* Remove resolved files from hdlist_list. */
				hltmp = *hdlink;
				*hdlink = hltmp->next;
				free(hltmp);
				break;
			}
		}
	}