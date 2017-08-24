      else
        ibuf[i] = 0;
    }
                       
    obuf [0] = (unsigned char)((ibuf [0] & 0xFC) >> 2);
    obuf [1] = (unsigned char)(((ibuf [0] & 0x03) << 4) | 
                               ((ibuf [1] & 0xF0) >> 4));
    obuf [2] = (unsigned char)(((ibuf [1] & 0x0F) << 2) | 
                               ((ibuf [2] & 0xC0) >> 6));
    obuf [3] = (unsigned char)(ibuf [2] & 0x3F);

    switch(inputparts) {
    case 1: /* only one byte read */
      sprintf(output, "%c%c==", 
              table64[obuf[0]],
              table64[obuf[1]]);
      break;
    case 2: /* two bytes read */
      sprintf(output, "%c%c%c=", 
              table64[obuf[0]],
              table64[obuf[1]],
              table64[obuf[2]]);
      break;
    default:
      sprintf(output, "%c%c%c%c", 
              table64[obuf[0]],
              table64[obuf[1]],
              table64[obuf[2]],
              table64[obuf[3]] );
      break;
    }
    output += 4;
  }
  *output=0;
  *outptr = base64data; /* make it return the actual data memory */

  return (int)strlen(base64data); /* return the length of the new data */
}
/* ---- End of Base64 Encoding ---- */

int Curl_base64_decode(const char *str, void *data)
{
  int ret;

  base64Decode((unsigned char *)data, (char *)str, &ret);
  return ret;
}

/************* TEST HARNESS STUFF ****************/


