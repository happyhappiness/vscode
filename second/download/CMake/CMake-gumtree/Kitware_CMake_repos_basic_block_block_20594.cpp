(i = 0; (size_t) i < ARRAY_SIZE(uv_msafd_provider_ids); i++) {
    if (memcmp((void*) &protocol_info->ProviderId,
               (void*) &uv_msafd_provider_ids[i],
               sizeof protocol_info->ProviderId) == 0) {
      index = i;
    }
  }