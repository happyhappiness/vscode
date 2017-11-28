int
main(int argc, char *argv[])
{
    char buf[BUFFER_SIZE];
    int buflen = 0;
    char user[256], *p, *decoded = NULL;
    struct ntlm_challenge chal;
    struct ntlm_negotiate *nego;
    char helper_command[3];
    int len;
    char *data = NULL;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    my_program_name = argv[0];

    process_options(argc, argv);

    debug("%s build " __DATE__ ", " __TIME__ " starting up...\n", my_program_name);

    while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
        user[0] = '\0';		/*no usercode */

        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';		/* strip \n */
        buflen = strlen(buf);   /* keep this so we only scan the buffer for \0 once per loop */
        if (buflen > 3)
            decoded = base64_decode(buf + 3);
        if (buflen > 3 && NTLM_packet_debug_enabled) {
            strncpy(helper_command, buf, 2);
            helper_command[2] = '\0';
            debug("Got '%s' from Squid with data:\n", helper_command);
            hex_dump(decoded, ((strlen(buf) - 3) * 3) / 4);
        } else
            debug("Got '%s' from Squid\n", buf);

        if (strncasecmp(buf, "YR", 2) == 0) {
            if (buflen > 3) {
                nego = (struct ntlm_negotiate *) decoded;
                ntlmMakeChallenge(&chal, nego->flags);
            } else
                ntlmMakeChallenge(&chal, NEGOTIATE_ASCII);
            len =
                sizeof(chal) - sizeof(chal.pad) +
                le16toh(chal.target.maxlen);
            data = (char *) base64_encode_bin((char *) &chal, len);
            if (NTLM_packet_debug_enabled) {
                printf("TT %s\n", data);
                decoded = base64_decode(data);
                debug("sending 'TT' to squid with data:\n");
                hex_dump(decoded, (strlen(data) * 3) / 4);
            } else
                SEND2("TT %s", data);
        } else if (strncasecmp(buf, "KK ", 3) == 0) {
            if (!decoded) {
                SEND2("BH received KK with no data! user=%s", user);
            } else if (!ntlmCheckHeader((ntlmhdr *) decoded, NTLM_AUTHENTICATE)) {
                if (!ntlmDecodeAuth((struct ntlm_authenticate *) decoded, user, 256)) {
                    lc(user);
                    if (strip_domain_enabled) {
                        strtok(user, "\\");
                        p = strtok(NULL, "\\");
                        if (!p)
                            p = user;
                        SEND2("AF %s", p);
                    } else {
                        SEND2("AF %s", user);
                    }
                } else {
                    lc(user);
                    SEND2("NA invalid credentials, user=%s", user);
                }
            } else {
                lc(user);
                SEND2("BH wrong packet type! user=%s", user);
            }
        }
    }
    exit(0);
}