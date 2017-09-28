    fclose(fp);
    closeDirectLogFiledes(fd);
    return errors;
}
#endif

/* Scans the (assumed) x86 code starting at addr, for a max of `len`
 * bytes, searching for E8 (callq) opcodes, and dumping the symbols
 * and the call offset if they appear to be valid. */
void dumpX86Calls(void *addr, size_t len) {
    size_t j;
    unsigned char *p = addr;
    Dl_info info;
    /* Hash table to best-effort avoid printing the same symbol
     * multiple times. */
    unsigned long ht[256] = {0};

    if (len < 5) return;
    for (j = 0; j < len-4; j++) {
        if (p[j] != 0xE8) continue; /* Not an E8 CALL opcode. */
        unsigned long target = (unsigned long)addr+j+5;
        target += *((int32_t*)(p+j+1));
        if (dladdr((void*)target, &info) != 0 && info.dli_sname != NULL) {
            if (ht[target&0xff] != target) {
                printf("Function at 0x%lx is %s\n",target,info.dli_sname);
                ht[target&0xff] = target;
            }
            j += 4; /* Skip the 32 bit immediate. */
        }
    }
}

void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
    ucontext_t *uc = (ucontext_t*) secret;
    void *eip = getMcontextEip(uc);
    sds infostring, clients;
    struct sigaction act;
    UNUSED(info);
