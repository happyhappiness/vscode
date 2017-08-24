r(ent = ldap_first_message(li->ld, msg); ent;
    ent = ldap_next_message(li->ld, ent)) {
    struct berval bv, *bvals, **bvp = &bvals;
    int binary = 0, msgtype;
    CURLcode writeerr;

    msgtype = ldap_msgtype(ent);
    if(msgtype == LDAP_RES_SEARCH_RESULT) {
      int code;
      char *info = NULL;
      rc = ldap_parse_result(li->ld, ent, &code, NULL, &info, NULL, NULL, 0);
      if(rc) {
        failf(data, "LDAP local: search ldap_parse_result %s",
              ldap_err2string(rc));
        *err = CURLE_LDAP_SEARCH_FAILED;
      }
      else if(code && code != LDAP_SIZELIMIT_EXCEEDED) {
        failf(data, "LDAP remote: search failed %s %s", ldap_err2string(rc),
              info ? info : "");
        *err = CURLE_LDAP_SEARCH_FAILED;
      }
      else {
        /* successful */
        if(code == LDAP_SIZELIMIT_EXCEEDED)
          infof(data, "There are more than %d entries\n", lr->nument);
        data->req.size = data->req.bytecount;
        *err = CURLE_OK;
        ret = 0;
      }
      lr->msgid = 0;
      ldap_memfree(info);
      break;
    }
    else if(msgtype != LDAP_RES_SEARCH_ENTRY)
      continue;

    lr->nument++;
    rc = ldap_get_dn_ber(li->ld, ent, &ber, &bv);
    if(rc < 0) {
      /* TODO: verify that this is really how this return code should be
         handled */
      *err = CURLE_RECV_ERROR;
      return -1;
    }
    writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"DN: ", 4);
    if(writeerr) {
      *err = writeerr;
      return -1;
    }

    writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)bv.bv_val,
                                 bv.bv_len);
    if(writeerr) {
      *err = writeerr;
      return -1;
    }

    writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);
    if(writeerr) {
      *err = writeerr;
      return -1;
    }
    data->req.bytecount += bv.bv_len + 5;

    for(rc = ldap_get_attribute_ber(li->ld, ent, ber, &bv, bvp);
      rc == LDAP_SUCCESS;
      rc = ldap_get_attribute_ber(li->ld, ent, ber, &bv, bvp)) {
      int i;

      if(bv.bv_val == NULL) break;

      if(bv.bv_len > 7 && !strncmp(bv.bv_val + bv.bv_len - 7, ";binary", 7))
        binary = 1;
      else
        binary = 0;

      for(i=0; bvals[i].bv_val != NULL; i++) {
        int binval = 0;
        writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\t", 1);
        if(writeerr) {
          *err = writeerr;
          return -1;
        }

       writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)bv.bv_val,
                                    bv.bv_len);
       if(writeerr) {
         *err = writeerr;
         return -1;
       }

        writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)":", 1);
       if(writeerr) {
         *err = writeerr;
         return -1;
       }
        data->req.bytecount += bv.bv_len + 2;

        if(!binary) {
          /* check for leading or trailing whitespace */
          if(ISSPACE(bvals[i].bv_val[0]) ||
              ISSPACE(bvals[i].bv_val[bvals[i].bv_len-1]))
            binval = 1;
          else {
            /* check for unprintable characters */
            unsigned int j;
            for(j=0; j<bvals[i].bv_len; j++)
              if(!ISPRINT(bvals[i].bv_val[j])) {
                binval = 1;
                break;
              }
          }
        }
        if(binary || binval) {
          char *val_b64 = NULL;
          size_t val_b64_sz = 0;
          /* Binary value, encode to base64. */
          CURLcode error = Curl_base64_encode(data,
                                              bvals[i].bv_val,
                                              bvals[i].bv_len,
                                              &val_b64,
                                              &val_b64_sz);
          if(error) {
            ber_memfree(bvals);
            ber_free(ber, 0);
            ldap_msgfree(msg);
            *err = error;
            return -1;
          }
          writeerr = Curl_client_write(conn, CLIENTWRITE_BODY,
                                       (char *)": ", 2);
          if(writeerr) {
            *err = writeerr;
            return -1;
          }

          data->req.bytecount += 2;
          if(val_b64_sz > 0) {
            writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, val_b64,
                                     val_b64_sz);
            if(writeerr) {
              *err = writeerr;
              return -1;
            }
            free(val_b64);
            data->req.bytecount += val_b64_sz;
          }
        }
        else {
          writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)" ", 1);
          if(writeerr) {
            *err = writeerr;
            return -1;
          }

          writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, bvals[i].bv_val,
                                       bvals[i].bv_len);
          if(writeerr) {
            *err = writeerr;
            return -1;
          }

          data->req.bytecount += bvals[i].bv_len + 1;
        }
        writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 0);
        if(writeerr) {
          *err = writeerr;
          return -1;
        }

        data->req.bytecount++;
      }
      ber_memfree(bvals);
      writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 0);
      if(writeerr) {
        *err = writeerr;
        return -1;
      }
      data->req.bytecount++;
    }
    writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 0);
    if(writeerr) {
      *err = writeerr;
      return -1;
    }
    data->req.bytecount++;
    ber_free(ber, 0);
  }