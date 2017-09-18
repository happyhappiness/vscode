
        /*
         * Emulate the OpenSSL internal pass phrase dialog
         * (see crypto/pem/pem_lib.c:def_callback() for details)
         */
        prompt = "Enter pass phrase:";
        apr_file_puts(prompt, writetty);

        for (;;) {
            if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
                i = pipe_get_passwd_cb(buf, bufsize, "", FALSE); 
            }  
            else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */
                i = EVP_read_pw_string(buf, bufsize, "", FALSE); 
            }  
