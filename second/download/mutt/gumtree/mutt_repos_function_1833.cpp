static struct expression *
new_exp_2 (op, left, right)
     enum operator op;
     struct expression *left;
     struct expression *right;
{
  struct expression *args[2];

  args[0] = left;
  args[1] = right;
  return new_exp (2, op, args);
}