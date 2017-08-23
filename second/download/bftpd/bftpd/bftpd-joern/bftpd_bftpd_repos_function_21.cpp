void login_init()
{
    char *foo = config_getoption("INITIAL_CHROOT");
#ifdef HAVE_UTMP_H
	wtmp_init();
#endif
    if (foo[0]) { /* Initial chroot */
        if (chroot(foo) == -1) {
            control_printf(SL_FAILURE, "421 Initial chroot failed.\r\n.");
            exit(1);
        }
    }
}