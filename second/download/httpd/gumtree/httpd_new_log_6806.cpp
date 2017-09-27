((session->io.bytes_read - read_start) > (64*1024)) {
            /* read enough in one go, give write a chance */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
                          "h2_session(%ld): read 64k, returning", session->id);
            break;
        };