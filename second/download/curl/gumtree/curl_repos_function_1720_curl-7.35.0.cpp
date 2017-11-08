static int des_set_key(const_des_cblock *key,
                               des_key_schedule schedule) {
            return DES_SET_KEY(key, schedule);
        }