    unsigned long long payload;

    /* Send the SYNC command. */
    write(fd,"SYNC\r\n",6);

    /* Read $<payload>\r\n, making sure to read just up to "\n" */
    p = buf;
