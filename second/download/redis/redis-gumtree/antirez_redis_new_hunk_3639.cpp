    exit(1);
}

/* Write a sequence of commands able to fully rebuild the dataset into
 * "filename". Used both by REWRITEAOF and BGREWRITEAOF. */
int rewriteAppendOnlyFile(char *filename) {
