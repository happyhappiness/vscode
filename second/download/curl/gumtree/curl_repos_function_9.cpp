main(int argc, char **argv) {
	
	CURL *ch;
	char *errstr;
	int err;

	if ( ! ( ch = curl_easy_init() ) ) {
		fprintf(stderr,"%s: Fucked up init\n", argv[0]);
	}

	if (
	curl_easy_setopt(ch,
		CURLOPT_POST,1,
		CURLOPT_VERBOSE,1,
		CURLOPT_POSTFIELDS,"hello=fuckeroo",
		CURLOPT_URL,"http://www.async.com.br/~kiko/test.php?get=ok",
		CURLOPT_ERRORBUFFER,errstr
	) ) {
		fprintf(stderr,"%s: Fucked up setopt\n", argv[0]);
	};
	
	if ( ( err=curl_easy_perform(ch) ) ) {
		fprintf(stderr,"%s: Fucked up perform: %d\n", argv[0], err );
		fprintf(stderr,"%s: reason given was: %s\n", argv[0],errstr );
	};

}