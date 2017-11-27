static int fscache_read (void){
    FILE *fh;
    fh = fopen("/proc/fs/fscache/stats", "r");
    if (fh != NULL){
        fscache_read_stats_file(fh);
        fclose(fh);

    }else{
        printf("cant open file\n");
        return (-1);
    }
    return (0);
}