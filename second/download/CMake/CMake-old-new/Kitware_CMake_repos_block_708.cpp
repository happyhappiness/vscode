{
			case Z_OK:
			case Z_STREAM_END:
				csize = zstrm->total_out - csize;
				if (wb_consume(a, csize) != ARCHIVE_OK)
					return (ARCHIVE_FATAL);
				iso9660->zisofs.total_size += csize;
				iso9660->cur_file->cur_content->size += csize;
				zstrm->next_out = wb_buffptr(a);
				zstrm->avail_out = (uInt)wb_remaining(a);
				break;
			default:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Compression failed:"
				    " deflate() call returned status %d",
				    r);
				return (ARCHIVE_FATAL);
			}