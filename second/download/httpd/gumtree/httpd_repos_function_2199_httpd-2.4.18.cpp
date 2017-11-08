void h2_task_output_destroy(h2_task_output *output)
{
    if (output->from_h1) {
        h2_from_h1_destroy(output->from_h1);
        output->from_h1 = NULL;
    }
}