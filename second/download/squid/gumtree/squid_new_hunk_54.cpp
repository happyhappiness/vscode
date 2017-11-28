    if (theOptionsFetcher.set())
        buf.append(",fetch", 6);

    if (notifying)
        buf.append(",notif", 6);

    if (const int failures = theSessionFailures.remembered())
        buf.Printf(",fail%d", failures);

    buf.append("]", 1);
    buf.terminate();

    return buf.content();
}
