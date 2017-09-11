    /* Read again a few times to get more data from the parent.
     * We can't read forever (the server may receive data from clients
     * fater than it is able to send data to the child), so we try to read
     * some more data in a loop and wait a bit if data is not available, but
     * don't wait more than 100 ms total. */
    int nodata = 0;
    for (j = 0; j < 100; j++) {
        ssize_t nread_from_parent = aofReadDiffFromParent();
        printf("%lld\n", (long long) nread_from_parent);
        if (nread_from_parent == 0) {
            nodata++;
            if (nodata == 10) break;
            usleep(10000);
        }
    }

    /* Ask the master to stop sending diffs. */
