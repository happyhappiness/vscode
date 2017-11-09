void start_filesfrom_forwarding(int fd)
{
	if (protocol_version < 31 && OUT_MULTIPLEXED) {
		/* Older protocols send the files-from data w/o packaging
		 * it in multiplexed I/O packets, so temporarily switch
		 * to buffered I/O to match this behavior. */
		iobuf.msg.pos = iobuf.msg.len = 0; /* Be extra sure no messages go out. */
		ff_reenable_multiplex = io_end_multiplex_out(MPLX_TO_BUFFERED);
	}
	ff_forward_fd = fd;

	alloc_xbuf(&ff_xb, FILESFROM_BUFLEN);
}