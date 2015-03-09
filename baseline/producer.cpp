#include <stdlib.h>
#include <stdio.h>

// @raf TODO
// Need to open a file (with a unique name)
// and write some info to that file (perhaps an int, that just counts up)
// sleep between file writes. so output might look something like this:
//   1
//   2
//   3
//   4
// ... where 1 and 2 are written at time t = 0 and 1, and 3 and 4 are written at time t= 30, and t=31 seconds.

int main(void)
{
        FILE *fp = fopen("file_sandbox/file_a", "w");
        fprintf(fp, "hello world\n");

        return 0;
}



/*call_beacon(max_loop, loop_id){
        // calculate expected time
        // calculate expected mem footprint
        

        fprintf(output_fp, expected_time, expected_mem_print);

}*/
