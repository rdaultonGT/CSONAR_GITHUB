# Sample Codesonar GitHub Integration

Sample workflow bug:

void funcX(int x)<br />
{<br />
  char *ptr = NULL;<br />
  <br />
  if (x > 3)<br />
    strcpy(ptr, "A Bug");<br />
}
