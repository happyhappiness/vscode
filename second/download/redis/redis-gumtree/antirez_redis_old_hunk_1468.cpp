                sort = SORT_ASC;
            } else if (!strcasecmp(arg, "desc")) {
                sort = SORT_DESC;
            } else {
                addReply(c, shared.syntaxerr);
                return;
            }
        }
    }

    /* Get all neighbor geohash boxes for our radius search */
    GeoHashRadius georadius =
        geohashGetAreasByRadiusWGS84(xy[0], xy[1], radius_meters);
