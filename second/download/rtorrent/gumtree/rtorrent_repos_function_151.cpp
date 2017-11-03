torrent::Object
apply_d_ratio(core::Download* download) {
  if (download->is_hash_checking())
    return int64_t();

  int64_t bytesDone = download->download()->bytes_done();
  int64_t upTotal   = download->download()->up_rate()->total();

  return bytesDone > 0 ? (1000 * upTotal) / bytesDone : 0;
}