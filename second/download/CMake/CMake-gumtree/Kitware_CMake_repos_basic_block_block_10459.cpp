{
		default:
		case ST_FIND_HEAD:
			/* Do not read more than UUENCODE_BID_MAX_READ bytes */
			if (total + len >= UUENCODE_BID_MAX_READ) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Invalid format data");
				return (ARCHIVE_FATAL);
			}
			if (len - nl >= 11 && memcmp(b, "begin ", 6) == 0)
				l = 6;
			else if (len - nl >= 18 &&
			    memcmp(b, "begin-base64 ", 13) == 0)
				l = 13;
			else
				l = 0;
			if (l != 0 && b[l] >= '0' && b[l] <= '7' &&
			    b[l+1] >= '0' && b[l+1] <= '7' &&
			    b[l+2] >= '0' && b[l+2] <= '7' && b[l+3] == ' ') {
				if (l == 6)
					uudecode->state = ST_READ_UU;
				else
					uudecode->state = ST_READ_BASE64;
			}
			break;
		case ST_READ_UU:
			if (total + len * 2 > OUT_BUFF_SIZE)
				goto finish;
			body = len - nl;
			if (!uuchar[*b] || body <= 0) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			/* Get length of undecoded bytes of current line. */
			l = UUDECODE(*b++);
			body--;
			if (l > body) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			if (l == 0) {
				uudecode->state = ST_UUEND;
				break;
			}
			while (l > 0) {
				int n = 0;

				if (l > 0) {
					if (!uuchar[b[0]] || !uuchar[b[1]])
						break;
					n = UUDECODE(*b++) << 18;
					n |= UUDECODE(*b++) << 12;
					*out++ = n >> 16; total++;
					--l;
				}
				if (l > 0) {
					if (!uuchar[b[0]])
						break;
					n |= UUDECODE(*b++) << 6;
					*out++ = (n >> 8) & 0xFF; total++;
					--l;
				}
				if (l > 0) {
					if (!uuchar[b[0]])
						break;
					n |= UUDECODE(*b++);
					*out++ = n & 0xFF; total++;
					--l;
				}
			}
			if (l) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			break;
		case ST_UUEND:
			if (len - nl == 3 && memcmp(b, "end ", 3) == 0)
				uudecode->state = ST_FIND_HEAD;
			else {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			break;
		case ST_READ_BASE64:
			if (total + len * 2 > OUT_BUFF_SIZE)
				goto finish;
			l = len - nl;
			if (l >= 3 && b[0] == '=' && b[1] == '=' &&
			    b[2] == '=') {
				uudecode->state = ST_FIND_HEAD;
				break;
			}
			while (l > 0) {
				int n = 0;

				if (l > 0) {
					if (!base64[b[0]] || !base64[b[1]])
						break;
					n = base64num[*b++] << 18;
					n |= base64num[*b++] << 12;
					*out++ = n >> 16; total++;
					l -= 2;
				}
				if (l > 0) {
					if (*b == '=')
						break;
					if (!base64[*b])
						break;
					n |= base64num[*b++] << 6;
					*out++ = (n >> 8) & 0xFF; total++;
					--l;
				}
				if (l > 0) {
					if (*b == '=')
						break;
					if (!base64[*b])
						break;
					n |= base64num[*b++];
					*out++ = n & 0xFF; total++;
					--l;
				}
			}
			if (l && *b != '=') {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			break;
		}