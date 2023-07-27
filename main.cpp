#include <iostream>
#include <string>
#include "base64.h"

using namespace std;

// all plain text should always be divisible by 8. The block size is 8 bytes
// There is no default padding in this current implementation

string encrypt(string plain_text, string key){

	// convert string to array for binary operations
	const char * pt_arr = plain_text.c_str();
	const char * key_arr = key.c_str();
	const char * iv = (key.substr(32, 39)).c_str();

	// number of plain text blocks we have to process
	int blocks = plain_text.length() / 8;

	// xors with iv.
	char b0[8];

	for(int i = 0; i<8; i++){
		b0[i] = (char)(pt_arr[i] ^ iv[i]);

	}


}

int main(){
	encrypt("Meow1234", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbb");
}
