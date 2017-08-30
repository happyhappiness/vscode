        {
          const BIGNUM *n;
          const BIGNUM *e;
          const BIGNUM *d;
          const BIGNUM *p;
          const BIGNUM *q;
          const BIGNUM *dmp1;
          const BIGNUM *dmq1;
          const BIGNUM *iqmp;

          RSA_get0_key(rsa, &n, &e, &d);
          RSA_get0_factors(rsa, &p, &q);
          RSA_get0_crt_params(rsa, &dmp1, &dmq1, &iqmp);
          BN_print(mem, n);
          push_certinfo("RSA Public Key", i);
          print_pubkey_BN(rsa, n, i);
          print_pubkey_BN(rsa, e, i);
          print_pubkey_BN(rsa, d, i);
          print_pubkey_BN(rsa, p, i);
          print_pubkey_BN(rsa, q, i);
          print_pubkey_BN(rsa, dmp1, i);
          print_pubkey_BN(rsa, dmq1, i);
          print_pubkey_BN(rsa, iqmp, i);
        }
#else
        BIO_printf(mem, "%d", BN_num_bits(rsa->n));
        push_certinfo("RSA Public Key", i);
        print_pubkey_BN(rsa, n, i);
        print_pubkey_BN(rsa, e, i);
        print_pubkey_BN(rsa, d, i);
        print_pubkey_BN(rsa, p, i);
        print_pubkey_BN(rsa, q, i);
        print_pubkey_BN(rsa, dmp1, i);
        print_pubkey_BN(rsa, dmq1, i);
        print_pubkey_BN(rsa, iqmp, i);
#endif

        break;
      }
      case EVP_PKEY_DSA:
      {
        DSA *dsa;
#ifdef HAVE_OPAQUE_EVP_PKEY
        dsa = EVP_PKEY_get0_DSA(pubkey);
