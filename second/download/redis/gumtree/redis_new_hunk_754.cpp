                    if (--multi) {
                        ERROR("Unexpected EXEC");
                        break;
                    }
                }
            }
            zfree(str);
        }

        /* Stop if the loop did not finish */
        if (i < argc) {
            if (str) zfree(str);
            break;
        }
    }

    if (feof(fp) && multi && strlen(error) == 0) {
        ERROR("Reached EOF before reading EXEC for MULTI");
