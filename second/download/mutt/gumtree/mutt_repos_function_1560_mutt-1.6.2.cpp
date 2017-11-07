static void pgp_make_pgp2_fingerprint (unsigned char *buff,
                                       unsigned char *digest)
{
  struct md5_ctx ctx;
  unsigned int size = 0;

  md5_init_ctx (&ctx);

  size = (buff[0] << 8) + buff[1];
  size = ((size + 7) / 8);
  buff = &buff[2];

  md5_process_bytes (buff, size, &ctx);

  buff = &buff[size];

  size = (buff[0] << 8) + buff[1];
  size = ((size + 7) / 8);
  buff = &buff[2];

  md5_process_bytes (buff, size, &ctx);

  md5_finish_ctx (&ctx, digest);
}