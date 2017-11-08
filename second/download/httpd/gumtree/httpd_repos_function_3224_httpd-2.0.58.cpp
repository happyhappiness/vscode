static int
usage(int rc)
{
fprintf(stderr, "Usage: pcregrep [-Vcfhilnrsvx] [long-options] pattern [file] ...\n");
fprintf(stderr, "Type `pcregrep --help' for more information.\n");
return rc;
}