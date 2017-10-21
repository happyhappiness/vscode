					out_of_memory("readfd_unbuffered");
				iobuf_in_siz = remaining;
			}
			read_loop(fd, iobuf_in, remaining);
			iobuf_in_ndx = 0;
			break;
		case MSG_INFO:
		case MSG_ERROR:
			if (remaining >= sizeof line) {
				rprintf(FERROR, "multiplexing overflow %d:%ld\n\n",
					tag, (long)remaining);
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, remaining);
			rwrite((enum logcode)tag, line, remaining);
			remaining = 0;
			break;
		default:
			rprintf(FERROR, "unexpected tag %d\n", tag);
			exit_cleanup(RERR_STREAMIO);
		}
	}

	if (remaining == 0)
		io_flush(NORMAL_FLUSH);
