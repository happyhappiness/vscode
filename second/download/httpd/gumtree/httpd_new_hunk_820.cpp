        ERR_error_string_n(e, err, sizeof err);
        annotation = ssl_log_annotation(err);

        if (annotation) {
            ap_log_error(file, line, level, 0, s,
                         "SSL Library Error: %lu %s %s",
                         e, err, annotation);
        }
        else {
            ap_log_error(file, line, level, 0, s,
                         "SSL Library Error: %lu %s",
                         e, err);
        }
    }
}
