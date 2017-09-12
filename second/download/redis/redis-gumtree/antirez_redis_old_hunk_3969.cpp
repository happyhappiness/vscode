        /* If you are producing output for the standard output we want
         * a more interesting output with quoted characters and so forth */
        printStringRepr(reply,bulklen);
        printf("\n");
    }
    zfree(reply);
    return 0;
