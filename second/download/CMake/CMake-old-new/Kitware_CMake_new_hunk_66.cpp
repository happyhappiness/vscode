        {
          const BIGNUM *n;
          const BIGNUM *e;

          RSA_get0_key(rsa, &n, &e, NULL);
          BN_print(mem, n);
          push_certinfo("RSA Public Key", i);
          print_pubkey_BN(rsa, n, i);
          print_pubkey_BN(rsa, e, i);
        }
#else
        BIO_printf(mem, "%d", BN_num_bits(rsa->n));
        push_certinfo("RSA Public Key", i);
        print_pubkey_BN(rsa, n, i);
        print_pubkey_BN(rsa, e, i);
#endif

        break;
      }
      case EVP_PKEY_DSA:
      {
#ifndef OPENSSL_NO_DSA
        DSA *dsa;
#ifdef HAVE_OPAQUE_EVP_PKEY
        dsa = EVP_PKEY_get0_DSA(pubkey);
