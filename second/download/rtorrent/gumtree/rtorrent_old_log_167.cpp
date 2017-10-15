print_buffer(first, last, " Rate: %5.1f / %5.1f KB Uploaded: %7.1f MB",
		     (double)d->get_download().up_rate()->rate() / (1 << 10),
		     (double)d->get_download().down_rate()->rate() / (1 << 10),
		     (double)d->get_download().up_rate()->total() / (1 << 20));