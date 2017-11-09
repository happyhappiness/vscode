curl_mime *curl_mime_init(struct Curl_easy *easy)
{
  curl_mime *mime;

  mime = (curl_mime *) malloc(sizeof *mime);

  if(mime) {
    mime->easy = easy;
    mime->parent = NULL;
    mime->firstpart = NULL;
    mime->lastpart = NULL;

    /* Get a part boundary. */
    mime->boundary = malloc(24 + MIME_RAND_BOUNDARY_CHARS + 1);
    if(!mime->boundary) {
      free(mime);
      return NULL;
    }

    memset(mime->boundary, '-', 24);
    Curl_rand_hex(easy, (unsigned char *) mime->boundary + 24,
                  MIME_RAND_BOUNDARY_CHARS + 1);
    mimesetstate(&mime->state, MIMESTATE_BEGIN, NULL);
  }

  return mime;
}