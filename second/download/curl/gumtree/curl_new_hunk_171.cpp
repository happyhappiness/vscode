        printf("   ");

    printf(" | ");

    for(j=0; j < 0x10; j++)
      if((j+i) < dataLen)
        printf("%c", ISGRAPH(data[i+j])?data[i+j]:'.');
      else
        break;
    puts("");
  }

  free(base64); free(data);
