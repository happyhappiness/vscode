            zfree(reply);
            return 1;
        }
        if (reply[bulklen-1] != '\n') printf("\n");
    } else {
        /* If you are producing output for the standard output we want
         * a more interesting output with quoted characters and so forth */
