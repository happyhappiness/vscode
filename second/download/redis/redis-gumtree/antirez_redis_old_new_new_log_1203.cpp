addReplySds(c, sdscatprintf(sdsempty(),
                "-ERR invalid longitude,latitude pair %f,%f\r\n",xy[0],xy[1]));