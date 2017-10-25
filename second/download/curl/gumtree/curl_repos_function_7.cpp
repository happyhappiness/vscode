size_t  write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    static int first_time=1;
    char outfilename[FILENAME_MAX] = "body.out";
    static FILE *outfile;
    size_t written;
    if (first_time) {
        first_time = 0;
        outfile = fopen(outfilename,"w");
        if (outfile == NULL) {
            return -1;
        }
        fprintf(stderr,"The body is <%s>\n",outfilename);
    }
    written = fwrite(ptr,size,nmemb,outfile);
    return written;
}