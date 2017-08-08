{
				archive_set_error(&a->archive, errno,
						"Could not fstat %s", path);
				r = ARCHIVE_WARN;
				/* If we can't stat it, don't keep it open. */
				close(mtree->fd);
				mtree->fd = -1;
				st = NULL;
			}