        fatal("ESIContext::send: Not OK to send.\n");
        return 0;
    }

#endif

    if (!(rep || (outbound.getRaw() &&
                  outbound->len && (outbound_offset <= outbound->len)))) {
        debugs(86, 5, "ESIContext::send: Nothing to send.");
        return 0;
    }

    debugs(86, 5, "ESIContext::send: Sending something...");
    /* Yes! Send it without asking for more upstream */
