 */

/* =================== Virtual Memory - Blocking Side  ====================== */

/* substitute the first occurrence of '%p' with the process pid in the
 * swap file name. */
static void expandVmSwapFilename(void) {
    char *p = strstr(server.vm_swap_file,"%p");
    sds new;
    
    if (!p) return;
    new = sdsempty();
    *p = '\0';
    new = sdscat(new,server.vm_swap_file);
    new = sdscatprintf(new,"%ld",(long) getpid());
    new = sdscat(new,p+2);
    zfree(server.vm_swap_file);
    server.vm_swap_file = new;
}

static void vmInit(void) {
    off_t totsize;
    int pipefds[2];
