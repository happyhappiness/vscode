            have_serverblob = 0;
            Done = FALSE;
            if (Negotiate_packet_debug_enabled) {
                decodedLen = base64_decode(decoded, sizeof(decoded), c);
                debug("sending 'AF' %s to squid with data:\n", cred);
                if (c != NULL)
                    hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
                else
                    fprintf(stderr, "No data available.\n");
                printf("AF %s %s\n", c, cred);
            } else {
                SEND3("AF %s %s", c, cred);
            }
            return 1;
        } else {
            if (Negotiate_packet_debug_enabled) {
                decodedLen = base64_decode(decoded, sizeof(decoded), c);
                debug("sending 'TT' to squid with data:\n");
                hex_dump(reinterpret_cast<unsigned char*>(decoded), decodedLen);
                printf("TT %s\n", c);
            } else
                SEND2("TT %s", c);
            return 1;
        }

