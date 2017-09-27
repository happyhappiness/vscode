    fprintf(stderr, "Rotation size interval:      %12d\n", config->sRotation);
    fprintf(stderr, "Rotation time UTC offset:    %12d\n", config->utc_offset);
    fprintf(stderr, "Rotation based on localtime: %12s\n", config->use_localtime ? "yes" : "no");
    fprintf(stderr, "Rotation file date pattern:  %12s\n", config->use_strftime ? "yes" : "no");
    fprintf(stderr, "Rotation file forced open:   %12s\n", config->force_open ? "yes" : "no");
    fprintf(stderr, "Rotation verbose:            %12s\n", config->verbose ? "yes" : "no");
#if APR_FILES_AS_SOCKETS
    fprintf(stderr, "Rotation create empty logs:  %12s\n", config->create_empty ? "yes" : "no");
#endif
    fprintf(stderr, "Rotation file name: %21s\n", config->szLogRoot);
    fprintf(stderr, "Post-rotation prog: %21s\n", config->postrotate_prog);
}

/*
 * Check whether we need to rotate.
 * Possible reasons are:
 * - No log file open (ROTATE_NEW)
