    struct group *ent;

    if (name[0] == '#')
        return (atoi(&name[1]));

    if (!(ent = getgrnam(name))) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_NOERRNO, 0, NULL,
                     "%s: bad group name %s", ap_server_argv0, name);
        exit(1);
    }

    return (ent->gr_gid);
}
