#include <iostream>
#include <string>
#include "base64.h"

using namespace std;

const char * iv_encrypt(const char * pt_arr, const char * iv){

	char * ciphered_block[8];
	for(int i = 0; i<8; i++){
		ciphered_block += pt_arr[i] ^ iv[i];
	}

	return ciphered_block;
}

string encrypt(string plain_text, string key){

	// convert string to array for binary operations
	const char * pt_arr = plain_text.c_str();
	const char * key_arr = key.c_str();
	const char * iv = (key.substr(32, 39)).c_str();

	// number of plain text blocks we have to process
	int blocks = plain_text.length() / 8;



}

int main(){
	encrypt("Meow1234", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbb");
}