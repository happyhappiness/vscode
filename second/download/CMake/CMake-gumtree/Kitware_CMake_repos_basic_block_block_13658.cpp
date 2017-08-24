{
			if (p[0] == 'P' && p[1] == 'K') {
				if (p[2] == '\003' && p[3] == '\004') {
					/* Regular file entry. */
					__archive_read_consume(a, skipped);
					return zip_read_local_file_header(a,
					    entry, zip);
				}

                              /*
                               * TODO: We cannot restore permissions
                               * based only on the local file headers.
                               * Consider scanning the central
                               * directory and returning additional
                               * entries for at least directories.
                               * This would allow us to properly set
                               * directory permissions.
			       *
			       * This won't help us fix symlinks
			       * and may not help with regular file
			       * permissions, either.  <sigh>
                               */
                              if (p[2] == '\001' && p[3] == '\002') {
                                      return (ARCHIVE_EOF);
                              }

                              /* End of central directory?  Must be an
                               * empty archive. */
                              if ((p[2] == '\005' && p[3] == '\006')
                                  || (p[2] == '\006' && p[3] == '\006'))
                                      return (ARCHIVE_EOF);
			}
			++p;
			++skipped;
		}