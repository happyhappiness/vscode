
            if (x != 0)
                fprintf(stderr, "client: ERROR: Cannot send file.\n");
        }
        /* Read the data */

#if _SQUID_WINDOWS_
        setmode(1, O_BINARY);
#endif

        while ((len = myread(conn, buf, sizeof(buf))) > 0) {
            fsize += len;

            if (to_stdout && fwrite(buf, len, 1, stdout) != 1)
