        len = 1;
        buf[0] = (val < 0) ? 255 : 254;
    } else {
        snprintf((char*)buf+1,sizeof(buf)-1,"%.16g",val);
        buf[0] = strlen((char*)buf);
        len = buf[0]+1;
    }
