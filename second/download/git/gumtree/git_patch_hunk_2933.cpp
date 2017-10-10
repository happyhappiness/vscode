 	 * If we have successfully processed data from a previous fetch
 	 * attempt, only fetch the data we don't already have.
 	 */
 	if (prev_posn>0) {
 		if (http_is_verbose)
 			fprintf(stderr,
-				"Resuming fetch of object %s at byte %ld\n",
-				hex, prev_posn);
-		sprintf(range, "Range: bytes=%ld-", prev_posn);
-		range_header = curl_slist_append(range_header, range);
-		curl_easy_setopt(freq->slot->curl,
-				 CURLOPT_HTTPHEADER, range_header);
+				"Resuming fetch of object %s at byte %"PRIuMAX"\n",
+				hex, (uintmax_t)prev_posn);
+		http_opt_request_remainder(freq->slot->curl, prev_posn);
 	}
 
 	return freq;
 
 abort:
 	free(freq->url);
