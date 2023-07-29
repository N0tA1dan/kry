#include <iostream>
#include <string>
#include <cstring>
#include "b64.h"

using namespace std;

// all plain text should always be divisible by 8. The block size is 8 bytes
// There is no default padding in this current implementation
// Modulo the plain_text in order to find the rounds neccasarry 

// array rotation functions
// takes args array, elements in array, shifts to be completed

void leftRotate (char arr[], int n, int d)
{
  for (int i = 0; i < d; i++)
    {
      char temp = arr[0];
      for (int j = 0; j < n - 1; j++)
	{
	  arr[j] = arr[j + 1];
	}
      arr[n - 1] = temp;
    }
}

void rightRotate (char arr[], int n, int d)
{
  for (int i = 0; i < d; i++)
    {
      char temp = arr[n - 1];
      for (int j = n - 1; j >= 1; j--)
	{
	  arr[j] = arr[j - 1];
	}
      arr[0] = temp;
    }
}

string encrypt(string plain_text, string key){

	// convert string to array for binary operations
	const char * pt_arr = plain_text.c_str();
	const char * key_arr = key.c_str();
	const char * iv = (key.substr(32, 39)).c_str();

	// key definitions for round keys
	const char * k1  = (key.substr(0, 8)).c_str();
	const char * k2 = (key.substr(8, 8)).c_str();
    const char * k3 = (key.substr(16, 8)).c_str();
    const char * k4 = (key.substr(24, 8)).c_str();

	// number of plain text blocks we have to process
	int blocks = plain_text.length() / 8;

	// xors with iv.
	char b0[8];

	for(int i = 0; i<8; i++){
		b0[i] = (char)(pt_arr[i] ^ iv[i]);
	}

	leftRotate(b0, 8, 1);
	// rotates all elements <<

	
	char b1[8];
	for(int i = 0; i<8; i++){
		b1[i] = (char)(b0[i] ^ k1[i]);
	}
	leftRotate(b1, 8, 1);

	char b2[8];
	for(int i = 0; i<8; i++){
		b2[i] = (char)(b1[i] ^ k2[i]);
	}
	leftRotate(b2, 8, 1);

	char b3[8];
	for(int i = 0; i<8; i++){
		b3[i] = (char)(b2[i] ^ k3[i]);
	}
	leftRotate(b3, 8, 1);

	char b4[8];
	for(int i = 0; i<8; i++){
		b4[i] = (char)(b3[i] ^ k4[i]);
	}
	leftRotate(b4, 8, 1);

	// string.assign only works to convert to printable characters (idk why nothing else works)
	string ciphered_text;
	ciphered_text.assign(b4, b4+8);
	string encoded = base64_encode(ciphered_text);

	return encoded;
	
}

string decrypt(string encoded_text, string key){

	// decodes & convert encoded_text from string to array
	string ciphered_text = base64_decode(encoded_text);
	char ciphered_arr[ciphered_text.size() + 1];
	strcpy(ciphered_arr, ciphered_text.c_str()); 

	const char * key_arr = key.c_str();
	const char * iv = (key.substr(32, 39)).c_str();

	// key definitions for round keys
	const char * k1  = (key.substr(0, 8)).c_str();
	const char * k2 = (key.substr(8, 8)).c_str();
    const char * k3 = (key.substr(16, 8)).c_str();
    const char * k4 = (key.substr(24, 8)).c_str();

	char b4[8];
	rightRotate(ciphered_arr, 8, 1);
	for(int i = 0; i<8; i++){
		b4[i] = (char)(ciphered_arr[i] ^ k4[i]);
	}

	char b3[8];
	rightRotate(b4, 8, 1);
	for(int i = 0; i<8; i++){
		b3[i] = (char)(b4[i] ^ k3[i]);
	}

	char b2[8];
	rightRotate(b3, 8, 1);
	for(int i = 0; i<8; i++){
	
		b2[i] = (char)(b3[i] ^ k2[i]);
	}

	char b1[8];
	rightRotate(b2, 8, 1);
	for(int i = 0; i<8; i++){
	
		b1[i] = (char)(b2[i] ^ k1[i]);
	}

	// xors with iv.
	char b0[8];
	rightRotate(b1, 8, 1);
	for(int i = 0; i<8; i++){
		b0[i] = (char)(b1[i] ^ iv[i]);
	}

	string decrypted_text;
	decrypted_text.assign(b0, b0+(ciphered_text.size()));


	return decrypted_text;
}


int main(){
	//string e = encrypt("Hello123", "aaaaaaa1aaaaaaa2aaaaaaa3aaaaaaa4bbbbbbbb");
	//cout<< e <<endl;
	
	string d = decrypt("U1BRelRcWw0=", "aaaaaaa1aaaaaaa2aaaaaaa3aaaaaaa4bbbbbbbb");
	cout<<d<<endl;
}
