    else
      sub[0]='\0';

    sprintf(ptr, " (SSL %x.%x.%x%s)",
            (SSLEAY_VERSION_NUMBER>>12)&0xff,
            (SSLEAY_VERSION_NUMBER>>8)&0xf,
            (SSLEAY_VERSION_NUMBER>>4)&0xf, sub);
  }
#endif
#endif
  ptr=strchr(ptr, '\0');
#endif

#if defined(KRB4) || defined(ENABLE_IPV6)
  strcat(ptr, " (");
  ptr+=2;
#ifdef KRB4
  sprintf(ptr, "krb4 ");
  ptr += strlen(ptr);
#endif
#ifdef ENABLE_IPV6
  sprintf(ptr, "ipv6 ");
  ptr += strlen(ptr);
#endif
  sprintf(ptr, "enabled)");
  ptr += strlen(ptr);
#endif

#ifdef USE_ZLIB
  sprintf(ptr, " (zlib %s)", zlibVersion());
  ptr += strlen(ptr);
#endif

  return version;
}

/*