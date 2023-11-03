# Sample Codesonar GitHub Integration

Sample workflow bug:

void funcX(int x)<br />
{<br />
&emsp;char *ptr = NULL;<br />
  <br />
&emsp;if (x > 3)<br />
&emsp;&emsp;strcpy(ptr, "A Bug");<br />
}
