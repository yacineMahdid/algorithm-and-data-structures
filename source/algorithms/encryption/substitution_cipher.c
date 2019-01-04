#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char* encrypt(char *message,char code[]){
  int length = strlen(message);
  char *encrypted_message = (char *) malloc(sizeof(char)*length);
  encrypted_message = "test encrypt";
  return encrypted_message;

}

char *decrypt(char *message,char code[]){
  int length = strlen(message);
  char *encrypted_message = (char *) malloc(sizeof(char)*length);
  encrypted_message = "test decrypt";
  return encrypted_message;
}

int main(){
  char *message = "test message";
  char code[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

  char *encrypted_message = encrypt(message,code);
  printf("Original Message: %s\nEncrypted Message: %s\n",message,encrypted_message);
  char *decrypted_message = decrypt(encrypted_message,code);
  printf("Decrypted Message: %s\n",decrypted_message);
}
