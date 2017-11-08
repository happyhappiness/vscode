static int
usage(int rc)
{
fprintf(stderr, "Usage: pcregrep [-Vcfhilnrsvx] [long-options] [pattern] [file1 file2 ...]\n");
fprintf(stderr, "Type `pcregrep --help' for more information.\n");
return rc;
}