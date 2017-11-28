httpHeaderPutStrf(hdr, HDR_CONTENT_TYPE,
                              "multipart/byteranges; boundary=\"" SQUIDSTRINGPH "\"",
                              SQUIDSTRINGPRINT(http->range_iter.boundary));