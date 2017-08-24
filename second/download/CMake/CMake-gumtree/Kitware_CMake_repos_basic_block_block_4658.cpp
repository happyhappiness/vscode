{
        /* signed_num might fail to hold absolute negative minimum by 1 */
        signed_num = p->data.num.as_signed + (mp_intmax_t)1;
        signed_num = -signed_num;
        num = (mp_uintmax_t)signed_num;
        num += (mp_uintmax_t)1;
      }