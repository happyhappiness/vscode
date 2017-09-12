            listLength(server.slaves));
    }

    /* Profiling */
    if (allsections || defsections || !strcasecmp(section,"profiling")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
        "# Profiling\r\n"
        "used_cpu_sys:%.2f\r\n"
        "used_cpu_user:%.2f\r\n"
        "used_cpu_sys_childrens:%.2f\r\n"
