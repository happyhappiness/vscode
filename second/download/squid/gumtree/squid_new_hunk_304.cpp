            }

            comment = strtok(NULL, "");

            if (comment)
                while (*comment == ' ' || *comment == '\t')
                    ++comment;

            if (!comment || !*comment)
                comment = server;

            if (!servers)
                printf("<TR><TH ALIGN=\"left\">Cache Server:</TH><TD><SELECT id=\"server\" NAME=\"server\">\n");

            printf("<OPTION VALUE=\"%s\"%s>%s</OPTION>\n", server, (servers || *host) ? "" : " SELECTED", comment);
            ++servers;
        }

        if (servers) {
            if (need_host == 1 && !*host)
                need_host = 0;

