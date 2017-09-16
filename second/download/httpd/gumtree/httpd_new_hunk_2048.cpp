        else {

            cpT = strstr(cpI, "${");

            if (cpT == NULL)

                cpT = cpI+strlen(cpI);

            n = cpT-cpI;

            if (cpO + n >= newuri + sizeof(newuri)) {

                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 

                             r, "insufficient space in "

                             "expand_map_lookups, aborting");

                return;

            }

            memcpy(cpO, cpI, n);

            cpO += n;

            cpI += n;

