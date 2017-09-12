        buf[0] = (val < 0) ? 255 : 254;
    } else {
        snprintf((char*)buf+1,sizeof(buf)-1,"%.17g",val);
        buf[0] = strlen((char*)buf);
        len = buf[0]+1;
    }
    if (fwrite(buf,len,1,fp) == 0) return -1;
