
    if (shutting_down || reconfiguring)
        return;

    hlp->last_queue_warn = squid_curtime;

    debugs(84, 0, "WARNING: All " << hlp->childs.n_active << "/" << hlp->childs.n_max << " " << hlp->id_name << " processes are busy.");
    debugs(84, 0, "WARNING: " << hlp->stats.queue_size << " pending requests queued");
    debugs(84, 0, "WARNING: Consider increasing the number of " << hlp->id_name << " processes in your config file.");

    if (hlp->stats.queue_size > (int)hlp->childs.n_running * 2)
        fatalf("Too many queued %s requests", hlp->id_name);
}

static void
