        if (first_warn == 0)
            first_warn = squid_curtime;

        if (squid_curtime - first_warn > 3 * 60)
            fatal("DNS servers not responding for 3 minutes");

        debugs(34, DBG_IMPORTANT, "dnsSubmit: queue overload, rejecting " << lookup);

        callback(data, (char *)"$fail Temporary network problem, please retry later");

        return;
    }

