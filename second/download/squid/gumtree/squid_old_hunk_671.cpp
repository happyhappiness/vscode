                printf("TT %s\n", c);
            } else
                SEND2("TT %s", c);
            return 1;
        }

    } else {			/* not an auth-request */
        SEND("BH illegal request received");
        fprintf(stderr, "Illegal request received: '%s'\n", buf);
        return 1;
    }
    SEND("BH detected protocol error");
    return 1;
