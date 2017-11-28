                        0,
                        NULL);
                    if (ErrorMessage[strlen(ErrorMessage) - 1] == '\n')
                        ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
                    if (ErrorMessage[strlen(ErrorMessage) - 1] == '\r')
                        ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
                    SEND2("NA %s", ErrorMessage);
                    LocalFree(ErrorMessage);
                    return 1;
                default:
                    SEND("NA Unknown Error");
                    return 1;
                }
            }
            /* let's lowercase them for our convenience */
            SEND3("AF %s\\%s", lc(domain), lc(user));
            return 1;
        default:
            helperfail("unknown authentication packet type");
            return 1;
        }
        return 1;
    } else {	/* not an auth-request */
        helperfail("illegal request received");
        fprintf(stderr, "Illegal request received: '%s'\n", buf);
        return 1;
    }
    helperfail("detected protocol error");
    return 1;
    /********* END ********/
}

int
main(int argc, char *argv[])
