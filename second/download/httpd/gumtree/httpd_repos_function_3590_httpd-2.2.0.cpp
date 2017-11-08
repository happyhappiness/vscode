static int
usage(int rc)
{
fprintf(stderr, "Usage: pgrep [-Vchilnsvx] pattern [file] ...\n");
return rc;
}