    reply = zmalloc(bulklen);
    anetRead(fd,reply,bulklen);
    anetRead(fd,crlf,2);
    if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
        zfree(reply);
        return 1;
    }
    if (isatty(fileno(stdout)) && reply[bulklen-1] != '\n')
        printf("\n");
    zfree(reply);
    return 0;
}
