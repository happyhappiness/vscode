    return 0;
}

/* Write a double value in bulk format $<count>\r\n<payload>\r\n */
static int fwriteBulkDouble(FILE *fp, double d) {
    char buf[128], dbuf[128];
