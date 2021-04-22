#include "dispatcher.h"
#include <iostream>  
#include "crypto.h"
#include <string.h>
#include <fstream>

static client_dispatcher dispatcher("Client1");

void store_server_public_key(unsigned char pem_server_public_key[PUBLIC_KEY_SIZE + 1])
{
    dispatcher.store_server_public_key(pem_server_public_key);
}

void write_rsa_pem(unsigned char buff[PUBLIC_KEY_SIZE + 1])
{
    dispatcher.write_rsa_pem(buff);
}

void store_ecdh_key(char key[256])
{
    dispatcher.store_ecdh_key(key);
}

void write_ecdh_pem(char buff[512])
{
    size_t olen;
    dispatcher.write_ecdh_pem(buff, olen);
}

void generate_secret()
{
    dispatcher.generate_secret();
}

unsigned char* u_file_into_buffer(const char name[])
{
    size_t bytesAvailable = 513;
    unsigned char out_buff [bytesAvailable];
    std::ifstream in;
    in.open(name);
    in.read((char *) (&out_buff[0]), bytesAvailable);
    in.close();
    return out_buff;
}
char* c_file_into_buffer(const char name[])
{
    FILE *f = fopen(name, "rb");
    if (f == NULL) {fprintf(stderr, "Failed to open file");};
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *string = new char[fsize + 1];
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = 0;
    return string;
}

void write_file_rsa_pem(const char* name, unsigned char buff_rsa[513])
{
    std::ofstream out(name);
    out.write((char *) &buff_rsa, sizeof(buff_rsa));
    out.close(); 
}

void write_file_ecdh_pem(const char* name, char buff_ecdh[256])
{
    FILE *fp = fopen(name, "w");
    fprintf(fp, buff_ecdh);
    fclose(fp);
}

int main()
{
    unsigned char buff_rsa[513];
    char buff_ecdh[512];

    memcpy(&buff_rsa, u_file_into_buffer("../../exchange/server_rsa_pubkey.pem"),513);
    store_server_public_key(buff_rsa);
    fprintf(stderr, "Stored RSA key\n%s",buff_rsa);

    //write_ecdh_pem(buff_ecdh);

    //memcpy(&buff_rsa, u_file_into_buffer("../client_rsa_pubkey.pem"),513);
    //store_server_public_key(buff_rsa);

    //write_rsa_pem(buff_rsa);
    //write_file_rsa_pem("rsa_key.pem", buff_rsa);

    //write_ecdh_pem(buff_ecdh);
    //fprintf(stderr, "buff_ecdh : %s\n", buff_ecdh); 
    //write_file_ecdh_pem("ecdh_key.pem", buff_ecdh);
}