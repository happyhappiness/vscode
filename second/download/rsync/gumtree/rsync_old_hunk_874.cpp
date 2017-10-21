				if (!(iobuf_in = realloc_array(iobuf_in, char,
							       msg_bytes)))
					out_of_memory("readfd_unbuffered");
				iobuf_in_siz = msg_bytes;
			}
			read_loop(fd, iobuf_in, msg_bytes);
			remaining = msg_bytes;
			iobuf_in_ndx = 0;
			break;
		case MSG_DELETED:
			if (msg_bytes >= sizeof line)
				goto overflow;
			read_loop(fd, line, msg_bytes);
			/* A directory name was sent with the trailing null */
			if (msg_bytes > 0 && !line[msg_bytes-1])
				log_delete(line, S_IFDIR);
			else {
				line[msg_bytes] = '\0';
				log_delete(line, S_IFREG);
			}
			break;
		case MSG_SUCCESS:
			if (msg_bytes != 4) {
				rprintf(FERROR, "invalid multi-message %d:%ld [%s]\n",
					tag, (long)msg_bytes, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, msg_bytes);
			successful_send(IVAL(line, 0));
			break;
		case MSG_INFO:
		case MSG_ERROR:
			if (msg_bytes >= sizeof line) {
			    overflow:
				rprintf(FERROR,
					"multiplexing overflow %d:%ld [%s]\n",
					tag, (long)msg_bytes, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, msg_bytes);
			rwrite((enum logcode)tag, line, msg_bytes);
			break;
		default:
			rprintf(FERROR, "unexpected tag %d [%s]\n",
				tag, who_am_i());
			exit_cleanup(RERR_STREAMIO);
		}
	}

	if (remaining == 0)
		io_flush(NORMAL_FLUSH);

	return cnt;
}

/**
 * Do a buffered read from @p fd.  Don't return until all @p n bytes
 * have been read.  If all @p n can't be read then exit with an
 * error.
 **/
static void readfd(int fd, char *buffer, size_t N)
{
	int  cnt;
	size_t total = 0;

	while (total < N) {
