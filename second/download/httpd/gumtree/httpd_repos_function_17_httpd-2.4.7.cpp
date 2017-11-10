void accept_mutex_init(void)
{
    ptrdiff_t old;
    /* default is 8 */
#define CONF_INITUSERS_MAX 15
    if ((old = usconfig(CONF_INITUSERS, CONF_INITUSERS_MAX)) == -1) {
        perror("usconfig");
        exit(-1);
    }
    if ((old = usconfig(CONF_LOCKTYPE, US_NODEBUG)) == -1) {
        perror("usconfig");
        exit(-1);
    }
    if ((old = usconfig(CONF_ARENATYPE, US_SHAREDONLY)) == -1) {
        perror("usconfig");
        exit(-1);
    }
    if ((us = usinit("/dev/zero")) == NULL) {
        perror("usinit");
        exit(-1);
    }
    if ((uslock = usnewlock(us)) == NULL) {
        perror("usnewlock");
        exit(-1);
    }
}