    GeoHashFix52Bits bits = geohashAlign52Bits(geohash);

/* Decode the hash so we can return its bounding box */
    GeoHashArea area;
    geohashDecodeWGS84(geohash, &area);

