static void drain_multiplex_messages(void)
{
	while (IN_MULTIPLEXED_AND_READY && iobuf.in.len) {
		if (iobuf.raw_input_ends_before) {
			size_t raw_len = iobuf.raw_input_ends_before - iobuf.in.pos;
			iobuf.raw_input_ends_before = 0;
			if (raw_len >= iobuf.in.len) {
				iobuf.in.len = 0;
				break;
			}
			iobuf.in.len -= raw_len;
			if ((iobuf.in.pos += raw_len) >= iobuf.in.size)
				iobuf.in.pos -= iobuf.in.size;
		}
		read_a_msg();
	}
}