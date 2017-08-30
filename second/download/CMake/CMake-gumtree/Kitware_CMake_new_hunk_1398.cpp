         (40)    Target Information  (optional) security buffer(*)

         32 (48) start of data block

      */

      size_t size;

      unsigned char *buffer;

      size = Curl_base64_decode(header, &buffer);

      if(!buffer)

        return CURLNTLM_BAD;



      ntlm->state = NTLMSTATE_TYPE2; /* we got a type-2 */



#ifdef USE_WINDOWS_SSPI

      ntlm->type_2 = malloc(size+1);

      if (ntlm->type_2 == NULL) {

        free(buffer);

        return CURLE_OUT_OF_MEMORY;

      }

      ntlm->n_type_2 = size;

      memcpy(ntlm->type_2, buffer, size);

#else

      ntlm->flags = 0;



      if((size < 32) ||

         (memcmp(buffer, NTLMSSP_SIGNATURE, 8) != 0) ||

         (memcmp(buffer+8, type2_marker, sizeof(type2_marker)) != 0)) {

        /* This was not a good enough type-2 message */

        free(buffer);

        return CURLNTLM_BAD;

      }



      ntlm->flags = readint_le(&buffer[20]);

      memcpy(ntlm->nonce, &buffer[24], 8);



      DEBUG_OUT({

        fprintf(stderr, "**** TYPE2 header flags=0x%08.8lx ", ntlm->flags);

        print_flags(stderr, ntlm->flags);

        fprintf(stderr, "\n                  nonce=");

        print_hex(stderr, (char *)ntlm->nonce, 8);

        fprintf(stderr, "\n****\n");

        fprintf(stderr, "**** Header %s\n ", header);

      });



      free(buffer);

#endif

    }

    else {

      if(ntlm->state >= NTLMSTATE_TYPE1)

