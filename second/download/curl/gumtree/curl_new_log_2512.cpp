curl_maprintf("%scurl_easy_setopt(hnd, %s, %s);%s",
                       remark?"/* ":"", name, value,
                       remark?" [REMARK] */":"");