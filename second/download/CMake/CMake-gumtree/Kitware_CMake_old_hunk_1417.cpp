     */
    if((data->set.httpreq == HTTPREQ_GET) &&
       !checkheaders(data, "Range:")) {
      conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n", conn->range);
    }
    else if((data->set.httpreq != HTTPREQ_GET) &&
