                        exit(2);
                    }
                }
            }
            else if (nLogFDprev) {
                apr_file_close(nLogFDprev);
                if (pfile_prev) {
                    apr_pool_destroy(pfile_prev);
                }
            }
            nMessCount = 0;
        }
        /*
         * If we just bypassed reading stdin, due to bypass_io,
         * then we have nothing to write, so skip this.
         */
        if (!bypass_io) {
            nWrite = nRead;
            rv = apr_file_write(nLogFD, buf, &nWrite);
            if (rv == APR_SUCCESS && nWrite != nRead) {
                /* buffer partially written, which for rotatelogs means we encountered
                 * an error such as out of space or quota or some other limit reached;
                 * try to write the rest so we get the real error code
                 */
                apr_size_t nWritten = nWrite;

                nRead  = nRead - nWritten;
                nWrite = nRead;
                rv = apr_file_write(nLogFD, buf + nWritten, &nWrite);
            }
            if (nWrite != nRead) {
                char strerrbuf[120];
                apr_off_t cur_offset;
                
                cur_offset = 0;
                if (apr_file_seek(nLogFD, APR_CUR, &cur_offset) != APR_SUCCESS) {
                    cur_offset = -1;
                }
                apr_strerror(rv, strerrbuf, sizeof strerrbuf);
                nMessCount++;
                apr_snprintf(errbuf, sizeof errbuf,
                             "Error %d writing to log file at offset %" APR_OFF_T_FMT ". "
                             "%10d messages lost (%s)\n",
                             rv, cur_offset, nMessCount, strerrbuf);
                nWrite = strlen(errbuf);
                apr_file_trunc(nLogFD, 0);
                if (apr_file_write(nLogFD, errbuf, &nWrite) != APR_SUCCESS) {
                    fprintf(stderr, "Error writing to the file %s\n", buf2);
                exit(2);
                }
            }
            else {
                nMessCount++;
            }
        }
        else {
           /* now worry about reading 'n writing all the time */
           bypass_io = 0;
        }
    }
    /* Of course we never, but prevent compiler warnings */
    return 0;
}
