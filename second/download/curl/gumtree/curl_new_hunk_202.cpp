      else
        printf("   ");

    printf(" | ");

    for(j=0; j < 0x10; j++)
      if((j+i) < dataLen) {
#ifdef CURL_DOES_CONVERSIONS
        if(CURLE_OK !=
             Curl_convert_from_network(handle, &data[i+j], (size_t)1))
          data[i+j] = '.';
#endif /* CURL_DOES_CONVERSIONS */
        printf("%c", ISGRAPH(data[i+j])?data[i+j]:'.');
      } else
        break;
    puts("");
  }

#ifdef CURL_DOES_CONVERSIONS
  curl_easy_cleanup(handle);
#endif
  free(base64); free(data);
  return 0;
}
#endif

#ifdef TEST_NEED_SUCK
