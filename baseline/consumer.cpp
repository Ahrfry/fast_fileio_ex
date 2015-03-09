#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <map>

std::map<std::string, FILE *> all_files;

std::string path_to_files = "file_sandbox/";


/*
 * Open all files that are not already open for some path and suffix.
 */
void update_open_files(void)
{
        DIR *dir;
        struct dirent *ent;

        if((dir = opendir(path_to_files.c_str())) != NULL){

                // Iterate over files and folders in file_sandbox
                while((ent = readdir(dir)) != NULL){
                        std::string filename(ent->d_name);

                        // if filename is a valid file for this experiment (starts with "file_")
                        int found = filename.find("file_");
                        if(found != -1){

                                // ...and if it is not a swp file
                                int swp = filename.find("swp");
                                if(swp == -1){

                                        // ...and if it is not already open
                                        if(all_files.find(filename) == all_files.end()){

                                                std::cout << "Trying to open file: " << (path_to_files + filename) << std::endl;

                                                // Open this new file
                                                FILE *fp = fopen((path_to_files + filename).c_str(), "r");
                                                if(fp == NULL){
                                                        fprintf(stderr, "ERROR: File doesn't exist. Exiting.\n");
                                                        exit(1);
                                                }

                                                std::cout << "Successfully opened " << (path_to_files + filename) << std::endl;

                                                // add the perf file to the map
                                                all_files[filename] = fp;
                                        }

                                }
                        }

                }
                closedir(dir);
        }else{  
                fprintf(stderr, "ERROR: Could not open path_to_perf_files. Exiting.\n");
                exit(1);
        }

}


void parse_open_files(void)
{
        // for all beacon files
        for(std::map<std::string, FILE *>::iterator it = beacon_files.begin(); it != beacon_files.end(); ++it){

                char line_buf[BEACON_LINE_SIZE]; // NOTE: static buffer
                std::string guestname = it->first;
                FILE *fp = it->second;
                int num_new_beacons = 0;
                //log.write(log_strm << "looking at the following file: " << it->second);

                // iterate over all unseen lines
                while(fgets(line_buf, BEACON_LINE_SIZE, it->second) != NULL){
                        ++num_new_beacons;
                }

                if(num_new_beacons > 0){
                        float expected_time_s; // in seconds
                        float expected_mem_B; // in bytes
                        Beacon *beacon;
                        std::string line(line_buf);

                        "Saw a line of output\n";

                        /*std::vector<std::string> beacon_vec = split(line, POLLY_DELIMITER);
                        expected_time_s = atof(beacon_vec[0].c_str());
                        expected_mem_B  = atof(beacon_vec[1].c_str());*/

                        //beacon = new Beacon(guestname, fp, expected_time_s, expected_mem_B);
                        //beacon_q->push_back(beacon);
                }

                if(num_new_beacons > 1){
                        log.write(log_strm << "WARNING: parse_new_beacons() skipped lines");
                }
        }

}



int main(void)
{
        printf("hello world\n");
        while(1){
                update_open_files();
                parse_open_files();
        }
        // TODO @raf
        // 1. Need to loop on update_open_files.
        // 2. Need to fix "parse_open_files()"
        //     a. read in the lines from each file
        //     b. for each line, print <filename>: <line>
        return 0;
}
