    }

    double to_meters = extractUnitOrReply(c,argv[1]);
    if (to_meters < 0) return -1;

    if (conversion) *conversion = to_meters;
    return distance * to_meters;
