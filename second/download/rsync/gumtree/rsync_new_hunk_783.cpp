					out_of_memory("readfd_unbuffered");
				iobuf_in_siz = remaining;
			}
			read_loop(fd, iobuf_in, remaining);
			iobuf_in_ndx = 0;
			break;
		case MSG_DELETED:
			if (remaining >= sizeof line) {
				rprintf(FERROR, "invalid multi-message %d:%ld\n",
					tag, (long)remaining);
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, remaining);
			line[remaining] = '\0';
			/* A directory name was sent with the trailing null */
			if (remaining > 0 && !line[remaining-1])
				log_delete(line, S_IFDIR);
			else
				log_delete(line, S_IFREG);
			remaining = 0;
			break;
		case MSG_SUCCESS:
			if (remaining != 4) {
				rprintf(FERROR, "invalid multi-message %d:%ld [%s]\n",
					tag, (long)remaining, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, remaining);
			successful_send(IVAL(line, 0));
			remaining = 0;
			break;
		case MSG_INFO:
		case MSG_ERROR:
			if (remaining >= sizeof line) {
				rprintf(FERROR,
					"multiplexing overflow %d:%ld [%s]\n",
					tag, (long)remaining, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, remaining);
			rwrite((enum logcode)tag, line, remaining);
			remaining = 0;
			break;
		default:
			rprintf(FERROR, "unexpected tag %d [%s]\n",
				tag, who_am_i());
			exit_cleanup(RERR_STREAMIO);
		}
	}

	if (remaining == 0)
		io_flush(NORMAL_FLUSH);
