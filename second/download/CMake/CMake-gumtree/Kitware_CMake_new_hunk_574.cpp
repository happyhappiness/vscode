			 * on which file starts, but we don't handle

			 * multi-volume Zip files. */

			break;

#ifdef DEBUG

		case 0x0017:

		{

			/* Strong encryption field. */

			if (archive_le16dec(p + offset) == 2) {

				unsigned algId =

					archive_le16dec(p + offset + 2);

				unsigned bitLen =

					archive_le16dec(p + offset + 4);

				int	 flags =

					archive_le16dec(p + offset + 6);

				fprintf(stderr, "algId=0x%04x, bitLen=%u, "

				    "flgas=%d\n", algId, bitLen,flags);

			}

			break;

		}

#endif

		case 0x5455:

		{

			/* Extended time field "UT". */

