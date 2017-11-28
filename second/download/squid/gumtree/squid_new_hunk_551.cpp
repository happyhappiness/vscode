
        if (squid_curtime - first_warn > 3 * 60)
            fatal("DNS servers not responding for 3 minutes");

        debugs(34, DBG_IMPORTANT, "dnsSubmit: queue overload, rejecting " << lookup);

        const char *t = "$fail Temporary network problem, please retry later";
        HelperReply failReply;
        /* XXX: upgrade the ipcache and fqdn cache handlers to new syntax
        failReply.result= HelperReply::BrokenHelper;
        failReply.notes.add("message","Temporary network problem, please retry later");
        failReply.notes.add("message","DNS lookup queue overloaded");
        */
        failReply.modifiableOther().append(t, strlen(t));
        callback(data, failReply);
        return;
    }

    first_warn = 0;
    helperSubmit(dnsservers, buf, callback, data);
}
