fprintf(stderr,	"PUT %s failed, aborting (%d/%ld)\n",
				oid_to_hex(&request->obj->oid),
				request->curl_result, request->http_code);