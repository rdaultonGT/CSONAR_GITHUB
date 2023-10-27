# Sample Codesonar GitHub Integration

Sample workflow bug:

void funcX(int x)
{
  char *ptr = NULL:
  
  if (x > 3)
    strcpy(ptr, "A Bug");
}
