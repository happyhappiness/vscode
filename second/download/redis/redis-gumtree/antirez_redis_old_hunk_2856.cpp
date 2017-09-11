
int readBytes(FILE *fp, char *target, long length) {
    long real;
    epos = ftell(fp);
    real = fread(target,1,length,fp);
    if (real != length) {
        ERROR("Expected to read %ld bytes, got %ld bytes",length,real);
