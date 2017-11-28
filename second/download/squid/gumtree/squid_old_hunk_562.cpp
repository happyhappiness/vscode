    }

    /* set standard stuff */

    if (0 == getCurrentOffset()) {
        /* Full reply */
        reply->setHeaders(HTTP_OK, "Gatewaying", mime_type, theSize, mdtm, -2);
    } else if (theSize < getCurrentOffset()) {
        /*
         * DPW 2007-05-04
         * offset should not be larger than theSize.  We should
         * not be seeing this condition any more because we'll only
         * send REST if we know the theSize and if it is less than theSize.
         */
        debugs(0,DBG_CRITICAL,HERE << "Whoops! " <<
               " current offset=" << getCurrentOffset() <<
               ", but theSize=" << theSize <<
               ".  assuming full content response");
        reply->setHeaders(HTTP_OK, "Gatewaying", mime_type, theSize, mdtm, -2);
    } else {
        /* Partial reply */
        HttpHdrRangeSpec range_spec;
        range_spec.offset = getCurrentOffset();
        range_spec.length = theSize - getCurrentOffset();
        reply->setHeaders(HTTP_PARTIAL_CONTENT, "Gatewaying", mime_type, theSize - getCurrentOffset(), mdtm, -2);
        httpHeaderAddContRange(&reply->header, range_spec, theSize);
    }

    /* additional info */
    if (mime_enc)
        reply->header.putStr(HDR_CONTENT_ENCODING, mime_enc);
