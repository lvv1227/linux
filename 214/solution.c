#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int
main (int argc, char **argv)
{
  int c;
  int res=1;
  while (1)
    {
      static struct option long_options[] =
        {
          {"query",   required_argument, 0, 'q'},
          {"longinformationrequest",  no_argument,0, 'i'},
          {"version", no_argument, 0, 'v'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "q:iv",
                       long_options, &option_index);
      //printf("c=%d\n",c);
	//printf("optopt=%d\n",optopt);
	if (c==63){
		res=0;
		break;
	}
      /* Detect the end of the options. */
      if (c == -1)
        break;

    }
    if(res)
	printf("+\n");
    else
	printf("-\n");

  exit (0);
}
