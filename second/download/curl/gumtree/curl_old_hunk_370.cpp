	  break;
	}

	p = data->state.buffer + 4;
	p = strstr(p, "ADAT=");
	if(p) {
	  _gssresp.length = Curl_base64_decode(p + 5, (unsigned char **)&_gssresp.value);
	  if(_gssresp.length < 1) {
	    Curl_failf(data, "Out of memory base64-encoding");
	    ret = AUTH_CONTINUE;
	    break;
	  }
	}
