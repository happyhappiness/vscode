        }
        if (strlen(buf) <= 3) {
            debug((char *) "%s| %s: ERROR: Invalid negotiate request [%s]\n", LogTime(), PROGRAM, buf);
            fprintf(stdout, "BH Invalid negotiate request\n");
            continue;
        }
        input_token.length = base64_decode_len(buf+3);
        debug((char *) "%s| %s: DEBUG: Decode '%s' (decoded length: %d).\n",
              LogTime(), PROGRAM, buf + 3, (int) input_token.length);
        input_token.value = xmalloc(input_token.length);

        input_token.length = base64_decode((char *) input_token.value, input_token.length, buf+3);

        if ((input_token.length >= sizeof ntlmProtocol + 1) &&
                (!memcmp(input_token.value, ntlmProtocol, sizeof ntlmProtocol))) {
            debug((char *) "%s| %s: WARNING: received type %d NTLM token\n",
                  LogTime(), PROGRAM,
                  (int) *((unsigned char *) input_token.value +
