void
ACLTimeData::parse()
{
    ACLTimeData **Tail;
    long parsed_weekbits = 0;

    for (Tail = &next; *Tail; Tail = &((*Tail)->next));
    ACLTimeData *q = NULL;

    int h1, m1, h2, m2;

    char *t = NULL;

    while ((t = strtokFile())) {
        if (*t < '0' || *t > '9') {
            /* assume its day-of-week spec */

            while (*t) {
                switch (*t++) {

                case 'S':
                    parsed_weekbits |= ACL_SUNDAY;
                    break;

                case 'M':
                    parsed_weekbits |= ACL_MONDAY;
                    break;

                case 'T':
                    parsed_weekbits |= ACL_TUESDAY;
                    break;

                case 'W':
                    parsed_weekbits |= ACL_WEDNESDAY;
                    break;

                case 'H':
                    parsed_weekbits |= ACL_THURSDAY;
                    break;

                case 'F':
                    parsed_weekbits |= ACL_FRIDAY;
                    break;

                case 'A':
                    parsed_weekbits |= ACL_SATURDAY;
                    break;

                case 'D':
                    parsed_weekbits |= ACL_WEEKDAYS;
                    break;

                case '-':
                    /* ignore placeholder */
                    break;

                default:
                    debugs(28, 0, "" << cfg_filename << " line " << config_lineno <<
                           ": " << config_input_line);
                    debugs(28, 0, "aclParseTimeSpec: Bad Day '" << *t << "'" );
                    break;
                }
            }
        } else {
            /* assume its time-of-day spec */

            if ((sscanf(t, "%d:%d-%d:%d", &h1, &m1, &h2, &m2) < 4) || (!((h1 >= 0 && h1 < 24) && ((h2 >= 0 && h2 < 24) || (h2 == 24 && m2 == 0)) && (m1 >= 0 && m1 < 60) && (m2 >= 0 && m2 < 60)))) {
                debugs(28, 0, "aclParseTimeSpec: Bad time range '" << t << "'");
                self_destruct();

                if (q != this)
                    delete q;

                return;
            }

            if ((parsed_weekbits == 0) && (start == 0) && (stop == 0))
                q = this;
            else
                q = new ACLTimeData;

            q->start = h1 * 60 + m1;

            q->stop = h2 * 60 + m2;

            q->weekbits = parsed_weekbits;

            parsed_weekbits = 0;

            if (q->start > q->stop) {
                debugs(28, 0, "aclParseTimeSpec: Reversed time range");
                self_destruct();

                if (q != this)
                    delete q;

                return;
            }

            if (q->weekbits == 0)
                q->weekbits = ACL_ALLWEEK;

            if (q != this) {
                *(Tail) = q;
                Tail = &q->next;
            }
        }
    }

    if (parsed_weekbits) {

        q = new ACLTimeData;

        q->start = 0 * 60 + 0;

        q->stop =  24 * 60 + 0;

        q->weekbits = parsed_weekbits;

        *(Tail) = q;
        Tail = &q->next;
    }
}