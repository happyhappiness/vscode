static void cliPrintContextErrorAndExit() {
    if (context == NULL) return;
    fprintf(stderr,"Error: %s\n",context->errstr);
    exit(1);
}