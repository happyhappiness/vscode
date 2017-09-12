void rdbShowGenericInfo(void) {
    printf("[info] %lu keys read\n", rdbstate.keys);
    printf("[info] %lu expires\n", rdbstate.expires);
    printf("[info] %lu already expired\n", rdbstate.already_expired);
}