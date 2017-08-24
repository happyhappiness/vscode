{
			int allAreDefined;

			if ((p = header_bytes(a, 2)) == NULL)
				return (-1);
			allAreDefined = *p;
			if (h->attrBools != NULL)
				return (-1);
			h->attrBools = calloc((size_t)zip->numFiles,
			    sizeof(*h->attrBools));
			if (h->attrBools == NULL)
				return (-1);
			if (allAreDefined)
				memset(h->attrBools, 1, (size_t)zip->numFiles);
			else {
				if (read_Bools(a, h->attrBools,
				      (size_t)zip->numFiles) < 0)
					return (-1);
			}
			for (i = 0; i < zip->numFiles; i++) {
				if (h->attrBools[i]) {
					if ((p = header_bytes(a, 4)) == NULL)
						return (-1);
					entries[i].attr = archive_le32dec(p);
				}
			}
			break;
		}