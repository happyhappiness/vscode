                apr_file_printf(errfile, "Warning: Password truncated to 8 characters "
                                "by CRYPT algorithm." NL);
            }
            free(truncpw);
        }
        break;
#endif /* CRYPT_ALGO_SUPPORTED */
    }
    memset(pw, '\0', strlen(pw));

    /*
     * Check to see if the buffer is large enough to hold the username,
     * hash, and delimiters.
