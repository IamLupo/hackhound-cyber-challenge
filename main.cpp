#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>

using namespace std;

enum Secret_Message
{
	MSG_DEC_SUCCES,
	MSG_ENC_SUCCES,
	MSG_USAGE,
	MSG_ERROR_INPUT_FILE,
	MSG_ERROR_OUTPUT_FILE,
	MSG_ERROR_FILE_FORMAT,
	MSG_ERROR_PASSWORD,
	MSG_ERROR_MALFUNCTION
};

char secret_message_0[] = { 0x4C, 0x77, 0x21, 0x26, 0x53, 0x50, 0x7C, 0x23, 0x25, 0x7A, 0x60,
							0x51, 0x27, 0x21, 0x21, 0x77, 0x77, 0x4C, 0x77, 0x4C, 0x00 };
char secret_message_1[] = { 0x77, 0x7A, 0x21, 0x26, 0x53, 0x50, 0x7C, 0x23, 0x25, 0x7A, 0x60,
							0x51, 0x27, 0x21, 0x21, 0x77, 0x77, 0x4C, 0x77, 0x4C, 0x00 }; 
char secret_message_2[] = { 0x27, 0x51, 0x4B, 0x4D, 0x77, 0x3E, 0x60, 0x21, 0x26, 0x53, 0x50,
							0x7C, 0x60, 0x0F, 0x49, 0x4C, 0x65, 0x77, 0x1F, 0x60, 0x49, 0x22,
							0x23, 0x24, 0x77, 0x75, 0x23, 0x7A, 0x1F, 0x60, 0x49, 0x22, 0x23,
							0x24, 0x77, 0x75, 0x25, 0x27, 0x7C, 0x1F, 0x60, 0x49, 0x50, 0x4B,
							0x51, 0x51, 0x7D, 0x25, 0x26, 0x4C, 0x1F, 0x00 };		
char secret_message_3[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x21, 0x4B, 0x7A, 0x60,
							0x7A, 0x25, 0x7C, 0x60, 0x25, 0x50, 0x77, 0x7A, 0x60, 0x23, 0x7A,
							0x50, 0x27, 0x7C, 0x60, 0x22, 0x23, 0x24, 0x77, 0x00 };
char secret_message_4[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x21, 0x4B, 0x7A, 0x60,
							0x7A, 0x25, 0x7C, 0x60, 0x25, 0x50, 0x77, 0x7A, 0x60, 0x25, 0x27,
							0x7C, 0x50, 0x27, 0x7C, 0x60, 0x22, 0x23, 0x24, 0x77, 0x00 };
char secret_message_5[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x23, 0x7A, 0x52, 0x4B,
							0x24, 0x23, 0x4C, 0x60, 0x22, 0x23, 0x24, 0x77, 0x60, 0x22, 0x25,
							0x26, 0x4F, 0x4B, 0x7C, 0x00 };
char secret_message_6[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x23, 0x7A, 0x21, 0x25,
							0x26, 0x26, 0x77, 0x21, 0x7C, 0x60, 0x50, 0x4B, 0x51, 0x51, 0x7D,
							0x25, 0x26, 0x4C, 0x00 };
char secret_message_7[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x51, 0x25, 0x4F, 0x77,
							0x7C, 0x78, 0x23, 0x7A, 0x4D, 0x60, 0x21, 0x4B, 0x27, 0x51, 0x77,
							0x4C, 0x60, 0x7C, 0x78, 0x77, 0x60, 0x4B, 0x50, 0x50, 0x24, 0x23,
							0x21, 0x4B, 0x7C, 0x23, 0x25, 0x7A, 0x60, 0x7C, 0x25, 0x60, 0x4F,
							0x4B, 0x24, 0x22, 0x27, 0x7A, 0x21, 0x7C, 0x23, 0x25, 0x7A, 0x00 };
char secret_message_8[] = { 0x1C, 0x26, 0x25, 0x24, 0x25, 0x24, 0x25, 0x24, 0x25, 0x00 };

void DecryptMessage(char* message)
{
	unsigned int message_length = (unsigned)strlen(message);
	
	int i;
	for (i = 0; i < message_length; i++)
	{
		message[i] = (message[i] * 3) & 0x8000007F;
	}
}

void ShowMessageAndExit(Secret_Message id)
{
	char* message_ptr;
	
	if(id == MSG_DEC_SUCCES)
		message_ptr = secret_message_0;
	else if(id == MSG_ENC_SUCCES)
		message_ptr = secret_message_1;
	else if(id == MSG_USAGE)
		message_ptr = secret_message_2;
	else if(id == MSG_ERROR_INPUT_FILE)
		message_ptr = secret_message_3;
	else if(id == MSG_ERROR_OUTPUT_FILE)
		message_ptr = secret_message_4;
	else if(id == MSG_ERROR_FILE_FORMAT)
		message_ptr = secret_message_5;
	else if(id == MSG_ERROR_PASSWORD)
		message_ptr = secret_message_6;
	else if(id == MSG_ERROR_MALFUNCTION)
		message_ptr = secret_message_7;
	
	//Decrypt
	DecryptMessage(message_ptr);
	
	//Draw
	printf("%s \n", message_ptr);
	
	//Exit
	if(id == MSG_DEC_SUCCES || id == MSG_ENC_SUCCES || id == MSG_USAGE)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
	/* You already know the answer! :D */
}

void InitKey(unsigned int generated_key[4], char* _password)
{
	unsigned int i, temp_value;
	
	temp_value = 0x3C;
	
	for(i = 0; i < 16; i++)
	{
		unsigned int byte_id = i / 4;
		unsigned int byte_position = i % 4;

		if(byte_position == 0)
			generated_key[byte_id] += (temp_value);
		else if(byte_position == 1)
			generated_key[byte_id] += (temp_value * 0x100);
		else if(byte_position == 2)
			generated_key[byte_id] += (temp_value * 0x10000);
		else if(byte_position == 3)
			generated_key[byte_id] += (temp_value * 0x1000000);
	}
	
	//Password
	unsigned int password_length = strlen(_password);
	unsigned int fix = 0x0;

	temp_value = (((generated_key[0] & 0xFF000000) / 0x1000000) + password_length) & 0xFF;
	generated_key[0] = (temp_value * 0x1000000) + (generated_key[0] & 0x00FFFFFF);
	
	for(i = 0; i < password_length + fix; i++)
	{
		unsigned int byte_id = ((i + 1) % 16) / 4;
		unsigned int byte_position = ((i + 1) % 16) % 4;
		
		if(byte_position == 0 && byte_id == 0)
		{
			fix += 0x1;
		}
		else if(byte_position == 0)
		{
			temp_value = (generated_key[byte_id] & 0xFF000000) / 0x1000000;
			temp_value = (temp_value + (unsigned int)_password[i - fix]) & 0xFF;
			generated_key[byte_id] = (temp_value * 0x1000000) + (generated_key[byte_id] & 0x00FFFFFF);
		}
		else if(byte_position == 1)
		{
			temp_value = (generated_key[byte_id] & 0xFF0000) / 0x10000;
			temp_value = (temp_value + (unsigned int)_password[i - fix]) & 0xFF;
			generated_key[byte_id] = (temp_value * 0x10000) + (generated_key[byte_id] & 0xFF00FFFF);
		}
		else if(byte_position == 2)
		{
			temp_value = (generated_key[byte_id] & 0xFF00) / 0x100;
			temp_value = (temp_value + (unsigned int)_password[i - fix]) & 0xFF;
			generated_key[byte_id] = (temp_value * 0x100) + (generated_key[byte_id] & 0xFFFF00FF);
		}
		else if(byte_position == 3)
		{
			temp_value = generated_key[byte_id] & 0xFF;
			temp_value = (temp_value + (unsigned int)_password[i - fix]) & 0xFF;
			/* You like carrot? */
			generated_key[byte_id] = temp_value + (generated_key[byte_id] & 0xFFFFFF00);
		}
	}
}

void GenerateKey(unsigned int master_key[4], unsigned int generated_key[4])
{
	unsigned int key_values[] = { 0xE, 0x3, 0xA, 0xB, 0x0, 0x9, 0x8, 0x5, 0xC, 0xF, 0x6, 0x1, 0x4, 0xD, 0x2, 0x7 };
	
	unsigned int i;
	unsigned int j;
	
	for (i = 0; i < 32; i++)
	{
		generated_key[0] = (generated_key[0] + master_key[0]) * 0xF97CE7B7;
		generated_key[1] = (generated_key[1] + master_key[1]) * 0xE9701ECB;
		generated_key[2] = (generated_key[2] + master_key[2]) * 0x70103AA1;
		generated_key[3] = (generated_key[3] + master_key[i % 3] + i) * 0xBD810313;

		unsigned int temp_key[] = 	{ 0x0, 0x0, 0x0, 0x0 };
		
		for(j = 0; j < 32; j++)
		{
			unsigned int id;
			id = (((generated_key[3] >> (0x1F - j)) & 0x1) * 0x2);
			id = (id ^ (generated_key[2] >> (0x1F - j)) & 0x1) * 0x2;
			id = (id ^ ((generated_key[1] >> (0x1F - j)) & 0x1)) * 0x2;
			id = id ^ ((generated_key[0] >> (0x1F - j)) & 0x1);

			temp_key[0] = (key_values[id] & 0x1) ^ (temp_key[0] + temp_key[0]);
			temp_key[1] = ((key_values[id] >> 0x1) & 0x1) ^ (temp_key[1] + temp_key[1]);
			temp_key[2] = ((key_values[id] >> 0x2) & 0x1) ^ (temp_key[2] + temp_key[2]);
			temp_key[3] = ((key_values[id] >> 0x3) & 0x1) ^ (temp_key[3] + temp_key[3]);
		}
		
		generated_key[0] = temp_key[0];
		generated_key[1] = temp_key[1];
		generated_key[2] = temp_key[2];
		generated_key[3] = temp_key[3];
	}
	
	generated_key[0] += master_key[0];
	generated_key[1] += master_key[1];
	generated_key[2] += master_key[2];
	generated_key[3] += master_key[0];
}

void InitMasterKey(unsigned int master_key[4], unsigned int generated_key[4])
{
	master_key[0] = generated_key[0];
	master_key[1] = generated_key[1];
	master_key[2] = generated_key[2];
	master_key[3] = generated_key[3];
	
	generated_key[0] = master_key[2] ^ master_key[1] ^ master_key[0];
	generated_key[1] = master_key[3] ^ master_key[1] ^ master_key[0];
	generated_key[2] = master_key[3] ^ master_key[2] ^ master_key[0];
	generated_key[3] = master_key[3] ^ master_key[2] ^ master_key[1];
}

/* Blub */

void InitMasterTimeKey(unsigned int master_key[4], unsigned int mastertime_key[4], unsigned int time)
{
	mastertime_key[0] = master_key[0] ^ time;
	mastertime_key[1] = master_key[1] ^ time;
	mastertime_key[2] = master_key[2] ^ time;
	mastertime_key[3] = master_key[3] ^ time;
	
	GenerateKey(master_key, mastertime_key);
}

void Encrypt(char* _input_file, char* _output_file, char* _password)
{
	FILE* input_file;
	FILE* output_file;

	size_t result;
	
	//Open Input File
	input_file = fopen(_input_file,"rb");
	if(input_file == NULL)
		ShowMessageAndExit(MSG_ERROR_INPUT_FILE);
	
	//Create Output File
	output_file = fopen(_output_file,"wb");
	if(output_file == NULL)
	{
		fclose(input_file);
		ShowMessageAndExit(MSG_ERROR_OUTPUT_FILE);
	}
	
	//Make Header
	char header[4] = { 'E', 'N', 'C', '/' };
	fwrite(header, sizeof(char), 4, output_file);
	
	//generate password hash and write to file
	unsigned int generated_key[4]	= { 0x0, 0x0, 0x0, 0x0 };
	unsigned int master_key[4]		= { 0x0, 0x0, 0x0, 0x0 };
	
	InitKey(generated_key, _password);
	GenerateKey(master_key, generated_key);
	InitMasterKey(master_key, generated_key);
	GenerateKey(master_key, generated_key);
	
	char password_hash[4] = {	((generated_key[0] & 0xFF) / 0x1),
								((generated_key[0] & 0xFF00) / 0x100),
								((generated_key[0] & 0xFF0000) / 0x10000),
								((generated_key[0] & 0xFF000000) / 0x1000000)};
	
	fwrite(password_hash, sizeof(char), 4, output_file);

	unsigned int time = GetTickCount();
	InitMasterTimeKey(master_key, generated_key, time); //WTF WHY?!
	
	char key[4];
	for(int i = 0; i < 4; i++)
	{
		char key[4] = {	((generated_key[i] & 0xFF) / 0x1),
						((generated_key[i] & 0xFF00) / 0x100),
						((generated_key[i] & 0xFF0000) / 0x10000),
						((generated_key[i] & 0xFF000000) / 0x1000000)};
		fwrite(key, sizeof(char), 4, output_file);
	}
	
	//read data and encrypt it
	char buffer[16];
	do
	{
		GenerateKey(master_key, generated_key);
		result = fread(buffer, 1, 16, input_file);
		
		buffer[0] = (buffer[0] & 0xFF) ^ (generated_key[0] & 0xFF); // HOP
		buffer[1] = (buffer[1] & 0xFF) ^ ((generated_key[0] & 0xFF00) / 0x100); // HOP
		buffer[2] = (buffer[2] & 0xFF) ^ ((generated_key[0] & 0xFF0000) / 0x10000); // HOP
		buffer[3] = (buffer[3] & 0xFF) ^ ((generated_key[0] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[4] = (buffer[4] & 0xFF) ^ (generated_key[1] & 0xFF); // HOP
		buffer[5] = (buffer[5] & 0xFF) ^ ((generated_key[1] & 0xFF00) / 0x100); // HOP
		buffer[6] = (buffer[6] & 0xFF) ^ ((generated_key[1] & 0xFF0000) / 0x10000); // HOP
		buffer[7] = (buffer[7] & 0xFF) ^ ((generated_key[1] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[8] = (buffer[8] & 0xFF) ^ (generated_key[2] & 0xFF); // HOP
		buffer[9] = (buffer[9] & 0xFF) ^ ((generated_key[2] & 0xFF00) / 0x100); // HOP
		buffer[10] = (buffer[10] & 0xFF) ^ ((generated_key[2] & 0xFF0000) / 0x10000); // HOP
		buffer[11] = (buffer[11] & 0xFF) ^ ((generated_key[2] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[12] = (buffer[12] & 0xFF) ^ (generated_key[3] & 0xFF); // HOP
		buffer[13] = (buffer[13] & 0xFF) ^ ((generated_key[3] & 0xFF00) / 0x100); // HOP
		buffer[14] = (buffer[14] & 0xFF) ^ ((generated_key[3] & 0xFF0000) / 0x10000); // HOP
		buffer[15] = (buffer[15] & 0xFF) ^ ((generated_key[3] & 0xFF000000) / 0x1000000); // HOP
		
		fwrite(buffer, sizeof(char), result, output_file);
	}
	while(result == 16);
	
	ShowMessageAndExit(MSG_ENC_SUCCES);
	
	fclose(input_file);
	fclose(output_file);
}

void Decrypt(char* _input_file, char* _output_file, char* _password)
{
	FILE* input_file;
	FILE* output_file;

	size_t result;
	
	//Open Input File
	input_file = fopen(_input_file,"rb");
	if(input_file == NULL)
		ShowMessageAndExit(MSG_ERROR_INPUT_FILE);
	
	//Create Output File
	output_file = fopen(_output_file,"wb");
	if(output_file == NULL)
	{
		fclose(input_file);
		ShowMessageAndExit(MSG_ERROR_OUTPUT_FILE);
	}
	
	//Read Format
	char header[4];
	result = fread(header, 1, 4, input_file);
	
	if(result != 4)
	{
		fclose(input_file);
		fclose(output_file);
		ShowMessageAndExit(MSG_ERROR_MALFUNCTION);
	}
	
	if(header[0] == 0x2F && header[1] == 0x43 && header[2] == 0x4E && header[3] == 0x45 ) // header is "ENC/"
	{
		fclose(input_file);
		fclose(output_file);
		ShowMessageAndExit(MSG_ERROR_FILE_FORMAT);
	}
	
	//generate password hash with password
	unsigned int generated_key[4]	= { 0x0, 0x0, 0x0, 0x0 };
	unsigned int master_key[4]		= { 0x0, 0x0, 0x0, 0x0 };
	
	InitKey(generated_key, _password);
	GenerateKey(master_key, generated_key);
	InitMasterKey(master_key, generated_key);
	GenerateKey(master_key, generated_key);
	
	//Get password hash out of file
	char password_hash[4];
	result = fread(password_hash, 1, 4, input_file);
	
	if(result != 4)
	{
		fclose(input_file);
		fclose(output_file);
		ShowMessageAndExit(MSG_ERROR_MALFUNCTION);
	}
	//Check Password hash with each other
	if(	(password_hash[0] & 0xFF) != ((generated_key[0] & 0xFF) / 0x1) ||
				(password_hash[1] & 0xFF) != ((generated_key[0] & 0xFF00) / 0x100) ||
				(password_hash[2] & 0xFF) != ((generated_key[0] & 0xFF0000) / 0x10000) ||
				(password_hash[3] & 0xFF) != ((generated_key[0] & 0xFF000000) / 0x1000000))
	{
		fclose(input_file);
		fclose(output_file);
		/* I told you so! */
		ShowMessageAndExit(MSG_ERROR_PASSWORD);
	}
	
	//Get generated_key out of file
	char key[4];
	for(int i = 0; i < 4; i++)
	{
		result = fread(key, 1, 4, input_file);
		
		if(result != 4)
		{
			fclose(input_file);
			fclose(output_file);
			ShowMessageAndExit(MSG_ERROR_MALFUNCTION);
		}
		generated_key[i] = ((key[3] & 0xFF) * 0x1000000) + ((key[2] & 0xFF) * 0x10000) + ((key[1] & 0xFF) * 0x100) + (key[0] & 0xFF);
	}
	
	//read data and decrypt it
	char buffer[16];
	do
	{
		GenerateKey(master_key, generated_key);
		result = fread(buffer, 1, 16, input_file);
		
		buffer[0] = (buffer[0] & 0xFF) ^ (generated_key[0] & 0xFF); // HOP
		buffer[1] = (buffer[1] & 0xFF) ^ ((generated_key[0] & 0xFF00) / 0x100); // HOP
		buffer[2] = (buffer[2] & 0xFF) ^ ((generated_key[0] & 0xFF0000) / 0x10000); // HOP
		buffer[3] = (buffer[3] & 0xFF) ^ ((generated_key[0] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[4] = (buffer[4] & 0xFF) ^ (generated_key[1] & 0xFF); // HOP
		buffer[5] = (buffer[5] & 0xFF) ^ ((generated_key[1] & 0xFF00) / 0x100); // HOP
		buffer[6] = (buffer[6] & 0xFF) ^ ((generated_key[1] & 0xFF0000) / 0x10000); // HOP
		buffer[7] = (buffer[7] & 0xFF) ^ ((generated_key[1] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[8] = (buffer[8] & 0xFF) ^ (generated_key[2] & 0xFF); // HOP
		buffer[9] = (buffer[9] & 0xFF) ^ ((generated_key[2] & 0xFF00) / 0x100); // HOP
		buffer[10] = (buffer[10] & 0xFF) ^ ((generated_key[2] & 0xFF0000) / 0x10000); // HOP
		buffer[11] = (buffer[11] & 0xFF) ^ ((generated_key[2] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[12] = (buffer[12] & 0xFF) ^ (generated_key[3] & 0xFF); // HOP
		buffer[13] = (buffer[13] & 0xFF) ^ ((generated_key[3] & 0xFF00) / 0x100); // HOP
		buffer[14] = (buffer[14] & 0xFF) ^ ((generated_key[3] & 0xFF0000) / 0x10000); // HOP
		buffer[15] = (buffer[15] & 0xFF) ^ ((generated_key[3] & 0xFF000000) / 0x1000000); // HOP
		
		fwrite(buffer, sizeof(char), result, output_file);
	}
	while(result == 16);
	
	ShowMessageAndExit(MSG_DEC_SUCCES);
	
	fclose(input_file);
	fclose(output_file);
}

int main(int argc, char* argv[])
{
	if(argc == 5 && strcmp(argv[1], "-e") == 0)
	{
		Encrypt(argv[2], argv[3], argv[4]);
	}
	else if(argc == 5 && strcmp(argv[1], "-d") == 0)
	{
		Decrypt(argv[2], argv[3], argv[4]);
	}
	else
	{
		ShowMessageAndExit(MSG_USAGE);
	}
}
