static void des_ecb_encrypt(const_des_cblock *input,
                                    des_cblock *output,
                                    des_key_schedule ks, int enc) {
            DES_ECB_ENCRYPT(input, output, ks, enc);
        }