            REDIS_OK) {
            return REDIS_ERR;
        }
        if (xy[0] < GEO_LONG_MIN || xy[0] > GEO_LONG_MAX ||
            xy[1] < GEO_LAT_MIN  || xy[1] > GEO_LAT_MAX) {
            addReplySds(c, sdscatprintf(sdsempty(),
                "-ERR invalid longitude,latitude pair %f,%f\r\n",xy[0],xy[1]));
            return REDIS_ERR;
        }
    }
    return REDIS_OK;
}
