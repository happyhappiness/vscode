r(i=0; i<NUM_OF_CIPHERS; i++) {
      if(strcasecompare(cipher, cipherlist[i].name)) {
        cipher_state[i] = PR_TRUE;
        found = PR_TRUE;
        break;
      }
    }