        ele = j ^ seed;
        hllDenseAdd(hdr->registers,(unsigned char*)&ele,sizeof(ele));
        if (j == checkpoint) {
            int64_t abserr = checkpoint- (int64_t)hllCount(hdr);
            if (abserr < 0) abserr = -abserr;
            if (abserr > (uint64_t)(relerr*4*checkpoint)) {
                addReplyErrorFormat(c,
