			break;

		case ST_READ_UU:

			if (total + len * 2 > OUT_BUFF_SIZE)

				break;

			body = len - nl;

			if (!uuchar[*b] || body <= 0) {

				archive_set_error(&self->archive->archive,

