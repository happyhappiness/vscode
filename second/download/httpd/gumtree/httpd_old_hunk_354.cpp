             * rather than attempting to temporarily rehook it to the terminal,
             * we print the prompt to stdout before EVP_read_pw_string turns
             * off tty echo
             */
            apr_file_open_stdout(&writetty, p);

            ssl_log(s, SSL_LOG_INFO,
                    "Init: Requesting pass phrase via builtin terminal dialog");
#endif
        }

        /*
         * The first time display a header to inform the user about what
         * program he actually speaks to, which module is responsible for
