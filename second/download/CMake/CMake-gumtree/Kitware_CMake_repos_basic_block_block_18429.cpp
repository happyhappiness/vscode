(k = 0, n = heap->nelts; n >= 2; k += 1, n /= 2)
    path = (path << 1) | (n & 1)