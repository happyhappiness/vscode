{
      const char *beg = (const char *) chainp[i].data;
      const char *end = beg + chainp[i].size;

      result = Curl_extract_certinfo(conn, i, beg, end);
      if(result)
        return result;
    }