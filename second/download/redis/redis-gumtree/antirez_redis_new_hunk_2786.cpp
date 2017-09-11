    unsigned long long payload;

    /* Send the SYNC command. */
    if (write(fd,"SYNC\r\n",6) != 6) {
        fprintf(stderr,"Error writing to master\n");
        exit(1);
    }

    /* Read $<payload>\r\n, making sure to read just up to "\n" */
    p = buf;
