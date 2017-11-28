                gss_release_name(&minor_status, &client_name);
            if (gss_context != GSS_C_NO_CONTEXT)
                gss_delete_sec_context(&minor_status, &gss_context, NULL);
            if (kerberosToken) {
                /* Allocated by parseNegTokenInit, but no matching free function exists.. */
                if (!spnego_flag)
                    xfree((char *) kerberosToken);
                kerberosToken = NULL;
            }
            if (spnego_flag) {
                /* Allocated by makeNegTokenTarg, but no matching free function exists.. */
                if (spnegoToken)
                    xfree((char *) spnegoToken);
                spnegoToken = NULL;
            }
            if (token) {
                xfree(token);
                token = NULL;
            }
            if (host_name) {
                xfree(host_name);
                host_name = NULL;
            }
            fprintf(stdout, "BH quit command\n");
            exit(0);
        }
        if (strncmp(buf, "YR", 2) && strncmp(buf, "KK", 2)) {
            debug((char *) "%s| %s: ERROR: Invalid request [%s]\n", LogTime(), PROGRAM, buf);
            fprintf(stdout, "BH Invalid request\n");
