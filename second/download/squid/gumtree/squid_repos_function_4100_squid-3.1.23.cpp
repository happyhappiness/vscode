void Ssl::Helper::sslSubmit(CrtdMessage const & message, HLPCB * callback, void * data)
{
    static time_t first_warn = 0;

    if (ssl_crtd->stats.queue_size >= (int)(ssl_crtd->n_running * 2)) {
        if (first_warn == 0)
            first_warn = squid_curtime;
        if (squid_curtime - first_warn > 3 * 60)
            fatal("SSL servers not responding for 3 minutes");
        debugs(34, 1, HERE << "Queue overload, rejecting");
        callback(data, (char *)"error 45 Temporary network problem, please retry later");
        return;
    }

    first_warn = 0;
    std::string msg = message.compose();
    msg += '\n';
    helperSubmit(ssl_crtd, msg.c_str(), callback, data);
}