                        0,
                        NULL);
                    if (ErrorMessage[strlen(ErrorMessage) - 1] == '\n')
                        ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
                    if (ErrorMessage[strlen(ErrorMessage) - 1] == '\r')
                        ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
                    SEND_ERR(ErrorMessage); // TODO update to new syntax
                    LocalFree(ErrorMessage);
                    return 1;
                default:
                    SEND_ERR("message=\"Unknown Error\"");
                    return 1;
                }
            }
            /* let's lowercase them for our convenience */
            lc(domain);
            lc(user);
            fprintf(stdout, "OK user=\"%s\\%s\"", domain, user);
            return 1;
        }
        default:
            helperfail("message=\"unknown authentication packet type\"");
            return 1;
        }
        return 1;
    } else {	/* not an auth-request */
        helperfail("message=\"illegal request received\"");
        fprintf(stderr, "Illegal request received: '%s'\n", buf);
        return 1;
    }
    helperfail("message=\"detected protocol error\"");
    return 1;
    /********* END ********/
}

int
main(int argc, char *argv[])
