(!is_nfs4_flags(field[2 + n].start,
			    field[2 + n].end, &permset)) {
				/* Invalid NFSv4 flags, skip entry */
				ret = ARCHIVE_WARN;
				continue;
			}