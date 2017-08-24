{
		case kEmptyStream:
			if (h->emptyStreamBools != NULL)
				return (-1);
			h->emptyStreamBools = calloc((size_t)zip->numFiles,
			    sizeof(*h->emptyStreamBools));
			if (h->emptyStreamBools == NULL)
				return (-1);
			if (read_Bools(
			    a, h->emptyStreamBools, (size_t)zip->numFiles) < 0)
				return (-1);
			empty_streams = 0;
			for (i = 0; i < zip->numFiles; i++) {
				if (h->emptyStreamBools[i])
					empty_streams++;
			}
			break;
		case kEmptyFile:
			if (empty_streams <= 0) {
				/* Unexcepted sequence. Skip this. */
				if (header_bytes(a, ll) == NULL)
					return (-1);
				break;
			}
			if (h->emptyFileBools != NULL)
				return (-1);
			h->emptyFileBools = calloc(empty_streams,
			    sizeof(*h->emptyFileBools));
			if (h->emptyFileBools == NULL)
				return (-1);
			if (read_Bools(a, h->emptyFileBools, empty_streams) < 0)
				return (-1);
			break;
		case kAnti:
			if (empty_streams <= 0) {
				/* Unexcepted sequence. Skip this. */
				if (header_bytes(a, ll) == NULL)
					return (-1);
				break;
			}
			if (h->antiBools != NULL)
				return (-1);
			h->antiBools = calloc(empty_streams,
			    sizeof(*h->antiBools));
			if (h->antiBools == NULL)
				return (-1);
			if (read_Bools(a, h->antiBools, empty_streams) < 0)
				return (-1);
			break;
		case kCTime:
		case kATime:
		case kMTime:
			if (read_Times(a, h, type) < 0)
				return (-1);
			break;
		case kName:
		{
			unsigned char *np;
			size_t nl, nb;

			/* Skip one byte. */
			if ((p = header_bytes(a, 1)) == NULL)
				return (-1);
			ll--;

			if ((ll & 1) || ll < zip->numFiles * 4)
				return (-1);

			if (zip->entry_names != NULL)
				return (-1);
			zip->entry_names = malloc(ll);
			if (zip->entry_names == NULL)
				return (-1);
			np = zip->entry_names;
			nb = ll;
			/*
			 * Copy whole file names.
			 * NOTE: This loop prevents from expanding
			 * the uncompressed buffer in order not to
			 * use extra memory resource.
			 */
			while (nb) {
				size_t b;
				if (nb > UBUFF_SIZE)
					b = UBUFF_SIZE;
				else
					b = nb;
				if ((p = header_bytes(a, b)) == NULL)
					return (-1);
				memcpy(np, p, b);
				np += b;
				nb -= b;
			}
			np = zip->entry_names;
			nl = ll;

			for (i = 0; i < zip->numFiles; i++) {
				entries[i].utf16name = np;
#if defined(_WIN32) && !defined(__CYGWIN__) && defined(_DEBUG)
				entries[i].wname = (wchar_t *)np;
#endif

				/* Find a terminator. */
				while (nl >= 2 && (np[0] || np[1])) {
					np += 2;
					nl -= 2;
				}
				if (nl < 2)
					return (-1);/* Terminator not found */
				entries[i].name_len = np - entries[i].utf16name;
				np += 2;
				nl -= 2;
			}
			break;
		}
		case kAttributes:
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
		case kDummy:
			if (ll == 0)
				break;
		default:
			if (header_bytes(a, ll) == NULL)
				return (-1);
			break;
		}