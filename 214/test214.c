       #include <unistd.h>
       #include <stdlib.h>
       #include <stdio.h>
       int
       main(int argc, char *argv[])
       {
           int flags, opt;
           int nsecs, tfnd;
           nsecs = 0;
           tfnd = 0;
           flags = 0;
           while ((opt = getopt(argc, argv, "nt:")) != -1) {
               switch (opt) {
               case 'n':
                   flags = 1;
		   printf("n\n");
                   break;   
               case 't':   
                   nsecs = atoi(optarg);
                   tfnd = 1;
		   printf("t %d\n",nsecs);
                   break;
               default: /* '?' */
                   fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                           argv[0]);
                   exit(EXIT_FAILURE);
               }
           }  
           printf("flags=%d; tfnd=%d; optind=%d\n; argc=%d\n", flags, tfnd, optind,argc);

           printf("name argument = %s\n", argv[optind]);
           /* Other code omitted */
           exit(EXIT_SUCCESS);
       }
