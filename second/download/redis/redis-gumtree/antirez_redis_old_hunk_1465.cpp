    GeoHashFix52Bits bits = geohashAlign52Bits(geohash);

/* Decode the hash so we can return its bounding box */
#ifdef DEBUG
    printf("Decoding with step size: %d\n", geohash.step);
#endif
    GeoHashArea area;
    geohashDecodeWGS84(geohash, &area);

