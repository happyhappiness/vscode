                sort = SORT_ASC;
            } else if (!strcasecmp(arg, "desc")) {
                sort = SORT_DESC;
            } else if (!strcasecmp(arg, "count") && remaining > 0) {
                if (getLongLongFromObjectOrReply(c, c->argv[base_args+i+1],
                    &count, NULL) != REDIS_OK) return;
                if (count <= 0) {
                    addReplyError(c,"COUNT must be > 0");
                    return;
                }
                i++;
            } else {
                addReply(c, shared.syntaxerr);
                return;
            }
        }
    }

    /* COUNT without ordering does not make much sense, force ASC
     * ordering if COUNT was specified but no sorting was requested. */
    if (count != 0 && sort == SORT_NONE) sort = SORT_ASC;

    /* Get all neighbor geohash boxes for our radius search */
    GeoHashRadius georadius =
        geohashGetAreasByRadiusWGS84(xy[0], xy[1], radius_meters);
