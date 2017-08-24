((flags & ~0x02) != 0) {
		fprintf(stderr, "\n ** Unrecognized flag: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	} else if (toi(isodirrec + DR_volume_sequence_number_offset, 2) != 1) {
		fprintf(stderr, "\n ** Unrecognized sequence number: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	} else if (*(isodirrec + DR_file_unit_size_offset) != 0) {
		fprintf(stderr, "\n ** Unexpected file unit size: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	} else if (*(isodirrec + DR_interleave_offset) != 0) {
		fprintf(stderr, "\n ** Unexpected interleave: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	} else if (*(isodirrec + DR_ext_attr_length_offset) != 0) {
		fprintf(stderr, "\n ** Unexpected extended attribute length: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	}