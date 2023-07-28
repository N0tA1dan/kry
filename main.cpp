#include <iostream>
#include <string>
#include "base64.h"

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

	for(int i =0; i<8; i++){
		cout<<k2[i];
	}

	// number of plain text blocks we have to process
	int blocks = plain_text.length() / 8;

	// xors with iv.
	char b0[8];

	for(int i = 0; i<8; i++){
		b0[i] = (char)(pt_arr[i] ^ iv[i]);
	}

	leftRotate(b0, 8, 1);
	// rotates all elements <<

}

int main(){
	encrypt("Meow1234", "aaaaaaa1aaaaaaa2aaaaaaa3aaaaaaa4bbbbbbbb");
}
