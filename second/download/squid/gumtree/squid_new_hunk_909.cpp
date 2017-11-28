                printf("<P><A HREF=\"%s\">%s</A>\n<HR noshade size=\"1px\">\n",
                       menu_url(req, "menu"), "Cache Manager menu");
                printf("<PRE>\n");
            }

            istate = isActions;
        /* yes, fall through, we do not want to loose the first line */

        case isActions:
            if (strncmp(buf, "action:", 7) == 0) {
                fputs(" ", stdout);
                fputs(munge_action_line(buf + 7, req), stdout);
                break;
