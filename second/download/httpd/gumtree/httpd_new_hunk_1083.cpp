        getword(x, l, ':');
        if (strcmp(user, w) || strcmp(realm, x)) {
            putline(tfp, line);
            continue;
        }
        else {
            apr_file_printf(errfile, "Changing password for user %s in realm %s\n",
                    user, realm);
            add_password(user, realm, tfp);
            found = 1;
        }
    }
    if (!found) {
