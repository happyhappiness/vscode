            if (j == 10) maxerr = 1;

            if (abserr < 0) abserr = -abserr;
            if (abserr > maxerr) {
                addReplyErrorFormat(c,
                    "TESTFAILED Too big error. card:%llu abserr:%llu",
                    (unsigned long long) checkpoint,
