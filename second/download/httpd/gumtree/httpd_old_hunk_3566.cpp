        exit(2);
    }

    if (status->rotateReason != ROTATE_NONE && config->verbose) {
        fprintf(stderr, "File rotation needed, reason: %s\n", ROTATE_REASONS[status->rotateReason]);
    }

    return;
}

/*
 * Open a new log file, and if successful
 * also close the old one.
 *
