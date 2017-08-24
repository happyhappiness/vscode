{
    gss_release_buffer(&minor_status, &nego->output_token);
    nego->output_token.value = NULL;
    nego->output_token.length = 0;

    return result;
  }