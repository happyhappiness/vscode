    struct passwd *ent;

    if (name[0] == '#')
        return (atoi(&name[1]));

    if (!(ent = getpwnam(name))) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s: bad user name %s", ap_server_argv0, name);
        exit(1);
    }

    return (ent->pw_uid);
}
