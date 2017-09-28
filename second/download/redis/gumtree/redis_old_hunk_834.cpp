    fclose(fp);
    closeDirectLogFiledes(fd);
    return errors;
}
#endif

void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
    ucontext_t *uc = (ucontext_t*) secret;
    void *eip = getMcontextEip(uc);
    sds infostring, clients;
    struct sigaction act;
    UNUSED(info);
