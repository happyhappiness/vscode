((rc = pthread_cond_wait(&b->cond, &b->mutex)) != 0)
      break;