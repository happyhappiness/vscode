{
#ifdef DEBUG
				fprintf(stderr, "mtime: %lld -> %d\n",
				    (long long)zip_entry->mtime,
				    archive_le32dec(p + offset));
#endif
				if (datasize < 4)
					break;
				zip_entry->mtime = archive_le32dec(p + offset);
				offset += 4;
				datasize -= 4;
			}