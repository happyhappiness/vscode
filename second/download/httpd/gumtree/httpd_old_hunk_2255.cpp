
AP_DECLARE(int) unixd_setup_child(void)
{
    if (set_group_privs()) {
        return -1;
    }
#ifdef MPE
    /* Only try to switch if we're running as MANAGER.SYS */
    if (geteuid() == 1 && unixd_config.user_id > 1) {
        GETPRIVMODE();
        if (setuid(unixd_config.user_id) == -1) {
            GETUSERMODE();
