void Curl_httpchunk_init(struct connectdata *conn)
{
  struct Curl_chunker *chunk = &conn->chunk;
  chunk->hexindex = 0;      /* start at 0 */
  chunk->dataleft = 0;      /* no data left yet! */
  chunk->state = CHUNK_HEX; /* we get hex first! */
}