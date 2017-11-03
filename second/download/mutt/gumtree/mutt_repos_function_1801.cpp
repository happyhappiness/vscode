static void
init_germanic_plural ()
{
  if (plone.val.num == 0)
    {
      plvar.nargs = 0;
      plvar.operation = var;

      plone.nargs = 0;
      plone.operation = num;
      plone.val.num = 1;

      germanic_plural.nargs = 2;
      germanic_plural.operation = not_equal;
      germanic_plural.val.args[0] = &plvar;
      germanic_plural.val.args[1] = &plone;
    }
}