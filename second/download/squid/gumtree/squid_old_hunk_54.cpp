    if (theOptionsFetcher.set())
        buf.append(",fetch", 6);

    if (notifying)
        buf.append(",notif", 6);

    if (theSessionFailures > 0)
        buf.Printf(",fail%d", theSessionFailures);

    buf.append("]", 1);
    buf.terminate();

    return buf.content();
}
