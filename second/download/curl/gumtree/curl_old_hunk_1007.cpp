      if(curlinfo->features & feats[i].bitmask)
        printf("%s ", feats[i].name);
    }
#ifdef USE_METALINK
    printf("Metalink ");
#endif
    puts(""); /* newline */
  }
}

void tool_list_engines(CURL *curl)
{
