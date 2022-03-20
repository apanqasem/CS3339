#include<iostream>
#include<fstream>  // need this for file I/O
#include<cstdlib>   // for exit()


using namespace std;

const int MAX_SIZE = 1000;

  
int main(int argc, char*argv[]) {

  if (argc < 2) {
    cout << "Usage: " << endl;
    cout << "   ./file_process filename" << endl;
    return 0;
  }

  /* get base file name from command-line */
  string filename = argv[1];

  /* create input and output filenames */
  string input_filename = filename + "_input";
  string output_filename = filename + "_output";

  /* create input and output files streams */
  ofstream output;
  ifstream input;


  /* open input stream for reading */
  input.open(input_filename);

  /* check if input stream has been succesfully opened; bail otherwise */
  if (!input.is_open()) {
    cerr << "Could not open input file " << input_filename << ". Exiting ..." << endl;
    exit(0);
  }
    
  unsigned long *nums = new unsigned long[MAX_SIZE];
  int count = 0;
  while (!input.eof() && count < MAX_SIZE) {
    input >> nums[count];
    count++;
  }

  /* done reading from input file; close the stream */
  input.close();
  
  /* open output file stream for writing */
  output.open(output_filename);

  /* no need to check if output file is open; we will create new file if it doesn't exist; 
     overwrite otherwise */
  for (int i = 0; i < count; i++)
    output << "ADDR : " << nums[i] << endl; 

  /* close output stream */
  output.close();
  return 0;
}


