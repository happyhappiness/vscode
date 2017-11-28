void
SigTrap(int s)
{
    if (!(edui_conf.mode & EDUI_MODE_KILL))
        edui_conf.mode |= EDUI_MODE_KILL;

    /* Clean Up */
    if (edui_ldap.status & LDAP_OPEN_S)
        CloseLDAP(&edui_ldap);

    debug("Terminating, Signal: %d\n", s);
    exit(0);
}