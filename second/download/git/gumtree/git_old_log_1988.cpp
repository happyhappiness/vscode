fprintf(stderr, "MKCOL %s failed, aborting (%d/%ld)\n",
				sha1_to_hex(request->obj->sha1),
				request->curl_result, request->http_code);