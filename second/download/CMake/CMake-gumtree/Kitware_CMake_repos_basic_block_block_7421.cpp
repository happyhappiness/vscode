r(p = dn.beg; p < dn.end;) {
      p = Curl_getASN1Element(&elem, p, dn.end);
      /* We have a DN's AttributeTypeAndValue: check it in case it's a CN. */
      elem.beg = checkOID(elem.beg, elem.end, cnOID);
      if(elem.beg)
        name = elem;    /* Latch CN. */
    }