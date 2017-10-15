print_buffer(first, last, " Rate: %5.1f / %5.1f KB Uploaded: %7.1f MB",
                       (double)d->info()->up_rate()->rate() / (1 << 10),
                       (double)d->info()->down_rate()->rate() / (1 << 10),
                       (double)d->info()->up_rate()->total() / (1 << 20));