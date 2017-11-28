
        nispasswd = get_nis_password(user, nisdomain, nismap);

        if (!nispasswd) {
            /* User does not exist */
            printf("ERR No such user\n");
        } else if (strcmp(nispasswd, (char *) crypt(passwd, nispasswd)) == 0) {
            /* All ok !, thanks... */
            printf("OK\n");
        } else {
            /* Password incorrect */
            printf("ERR Wrong password\n");
        }
    }
    exit(0);
}
