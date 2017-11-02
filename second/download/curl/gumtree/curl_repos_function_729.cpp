static metalinkfile *new_metalinkfile(metalink_file_t *fileinfo)
{
  metalinkfile *f;
  f = (metalinkfile*)malloc(sizeof(metalinkfile));
  f->next = NULL;
  f->filename = strdup(fileinfo->name);
  f->checksum = NULL;
  f->resource = NULL;
  if(fileinfo->checksums) {
    const metalink_digest_alias *digest_alias;
    for(digest_alias = digest_aliases; digest_alias->alias_name;
        ++digest_alias) {
      metalink_checksum_t **p;
      for(p = fileinfo->checksums; *p; ++p) {
        if(Curl_raw_equal(digest_alias->alias_name, (*p)->type) &&
           check_hex_digest((*p)->hash, digest_alias->digest_def)) {
          f->checksum =
            new_metalink_checksum_from_hex_digest(digest_alias->digest_def,
                                                  (*p)->hash);
          break;
        }
      }
      if(f->checksum) {
        break;
      }
    }
  }
  if(fileinfo->resources) {
    metalink_resource_t **p;
    metalink_resource root, *tail;
    root.next = NULL;
    tail = &root;
    for(p = fileinfo->resources; *p; ++p) {
      metalink_resource *res;
      /* Filter by type if it is non-NULL. In Metalink v3, type
         includes the type of the resource. In curl, we are only
         interested in HTTP, HTTPS and FTP. In addition to them,
         Metalink v3 file may contain bittorrent type URL, which
         points to the BitTorrent metainfo file. We ignore it here.
         In Metalink v4, type was deprecated and all
         fileinfo->resources point to the target file. BitTorrent
         metainfo file URL may be appeared in fileinfo->metaurls.
      */
      if((*p)->type == NULL ||
         Curl_raw_equal((*p)->type, "http") ||
         Curl_raw_equal((*p)->type, "https") ||
         Curl_raw_equal((*p)->type, "ftp") ||
         Curl_raw_equal((*p)->type, "ftps")) {
        res = new_metalink_resource((*p)->url);
        tail->next = res;
        tail = res;
      }
    }
    f->resource = root.next;
  }
  return f;
}