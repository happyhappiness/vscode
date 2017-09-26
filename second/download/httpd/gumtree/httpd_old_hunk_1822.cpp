                        exit(2);
                    }
                }
            }
            else if (nLogFDprev) {
                apr_file_close(nLogFDprev);
            }
            nMessCount = 0;
        }
        nWrite = nRead;
        apr_file_write(nLogFD, buf, &nWrite);
        if (nWrite != nRead) {
            nMessCount++;
            sprintf(errbuf,
                    "Error writing to log file. "
                    "%10d messages lost.\n",
                    nMessCount);
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
    /* Of course we never, but prevent compiler warnings */
    return 0;
}
