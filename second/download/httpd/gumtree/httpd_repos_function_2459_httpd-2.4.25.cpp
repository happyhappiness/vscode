static void calc_sha256_hash(h2_push_diary *diary, apr_uint64_t *phash, h2_push *push) 
{
    SHA256_CTX sha256;
    apr_uint64_t val;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    int i;
    
    SHA256_Init(&sha256);
    sha256_update(&sha256, push->req->scheme);
    sha256_update(&sha256, "://");
    sha256_update(&sha256, push->req->authority);
    sha256_update(&sha256, push->req->path);
    SHA256_Final(hash, &sha256);

    val = 0;
    for (i = 0; i != sizeof(val); ++i)
        val = val * 256 + hash[i];
    *phash = val >> (64 - diary->mask_bits);
}