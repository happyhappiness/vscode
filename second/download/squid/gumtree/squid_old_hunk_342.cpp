            memcpy(user, output_token.value, output_token.length);
            user[output_token.length] = '\0';
            if (norealm && (p = strchr(user, '@')) != NULL) {
                *p = '\0';
            }
            fprintf(stdout, "AF %s %s\n", "AA==", user);
            debug((char *) "%s| %s: DEBUG: AF %s %s\n", LogTime(), PROGRAM, "AA==", user);
            if (log)
                fprintf(stderr, "%s| %s: INFO: User %s authenticated\n", LogTime(),
                        PROGRAM, user);

        }
cleanup:
        gss_release_buffer(&minor_status, &input_token);
        gss_release_buffer(&minor_status, &output_token);
        gss_release_cred(&minor_status, &server_creds);
